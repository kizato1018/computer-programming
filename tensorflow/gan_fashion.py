# TensorFlow and tf.keras
import tensorflow as tf
from tensorflow import keras


# Helper libraries
import numpy as np
import matplotlib.pyplot as plt

print(tf.__version__)

fashion_mnist = keras.datasets.fashion_mnist

(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

train_images, test_images = np.expand_dims(train_images, -1), np.expand_dims(test_images, -1)
# train_images = train_images.reshape(len(train_images),-1)
# train_labels = keras.utils.to_categorical(train_labels, 10)

# inputs = keras.layers.Input(shape=(784,))



class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

# plt.figure()
# plt.imshow(train_images[0])
# plt.colorbar()
# plt.grid(False)
# plt.show()

train_images = train_images / 255.0

test_images = test_images / 255.0

def load_real_samples():
	# load dataset
	(trainX, _), (_, _) = fashion_mnist.load_data()
	# expand to 3d, e.g. add channels
	X = np.expand_dims(trainX, axis=-1)
	# convert from ints to floats
	X = X.astype('float32')
	# scale from [0,255] to [-1,1]
	X = (X - 127.5) / 127.5
	return X

def generate_real_samples(dataset, n_samples):
	# choose random instances
	ix = np.random.randint(0, dataset.shape[0], n_samples)
	# select images
	X = dataset[ix]
	# generate class labels
	y = np.ones((n_samples, 1))
	return X, y

# generate points in latent space as input for the generator
def generate_latent_points(latent_dim, n_samples):
	# generate points in the latent space
	x_input = np.random.randn(latent_dim * n_samples)
	# reshape into a batch of inputs for the network
	x_input = x_input.reshape(n_samples, latent_dim)
	return x_input

# use the generator to generate n fake examples, with class labels
def generate_fake_samples(generator, latent_dim, n_samples):
	# generate points in latent space
	x_input = generate_latent_points(latent_dim, n_samples)
	# predict outputs
	X = generator.predict(x_input)
	# create class labels
	y = np.zeros((n_samples, 1))
	return X, y
# plt.figure(figsize=(10,10))
# for i in range(25):
#     plt.subplot(5,5,i+1)
#     plt.xticks([])
#     plt.yticks([])
#     plt.grid(False)
#     plt.imshow(train_images[i], cmap=plt.cm.binary)
#     plt.xlabel(class_names[train_labels[i]])
# plt.show()

def define_discriminator(in_shape=(28,28,1)):
	model = keras.Sequential()
	# downsample
	model.add(keras.layers.Conv2D(128, (3,3), strides=(2,2), padding='same', input_shape=in_shape))
	model.add(keras.layers.LeakyReLU(alpha=0.2))
	# downsample
	model.add(keras.layers.Conv2D(128, (3,3), strides=(2,2), padding='same'))
	model.add(keras.layers.LeakyReLU(alpha=0.2))
	# classifier
	model.add(keras.layers.Flatten())
	model.add(keras.layers.Dropout(0.4))
	model.add(keras.layers.Dense(1, activation='sigmoid'))
	# compile model
	opt = keras.optimizers.Adam(lr=0.0002, beta_1=0.5)
	model.compile(loss='binary_crossentropy', optimizer=opt, metrics=['accuracy'])
	return model
def define_generator(latent_dim):
	model = keras.Sequential()
	# foundation for 7x7 image
	n_nodes = 128 * 7 * 7
	model.add(keras.layers.Dense(n_nodes, input_dim=latent_dim))
	model.add(keras.layers.LeakyReLU(alpha=0.2))
	model.add(keras.layers.Reshape((7, 7, 128)))
	# upsample to 14x14
	model.add(keras.layers.Conv2DTranspose(128, (4,4), strides=(2,2), padding='same'))
	model.add(keras.layers.LeakyReLU(alpha=0.2))
	# upsample to 28x28
	model.add(keras.layers.Conv2DTranspose(128, (4,4), strides=(2,2), padding='same'))
	model.add(keras.layers.LeakyReLU(alpha=0.2))
	# generate
	model.add(keras.layers.Conv2D(1, (7,7), activation='tanh', padding='same'))
	return model
def define_gan(generator, discriminator):
	# make weights in the discriminator not trainable
	discriminator.trainable = False
	# connect them
	model = keras.Sequential()
	# add generator
	model.add(generator)
	# add the discriminator
	model.add(discriminator)
	# compile model
	opt = keras.optimizers.Adam(lr=0.0002, beta_1=0.5)
	model.compile(loss='binary_crossentropy', optimizer=opt)
	return model

def train(g_model, d_model, gan_model, dataset, latent_dim, n_epochs=100, n_batch=128):
	bat_per_epo = int(dataset.shape[0] / n_batch)
	half_batch = int(n_batch / 2)
	# manually enumerate epochs
	for i in range(n_epochs):
		# enumerate batches over the training set
		for j in range(bat_per_epo):
			# get randomly selected 'real' samples
			X_real, y_real = generate_real_samples(dataset, half_batch)
			# update discriminator model weights
			d_loss1, _ = d_model.train_on_batch(X_real, y_real)
			# generate 'fake' examples
			X_fake, y_fake = generate_fake_samples(g_model, latent_dim, half_batch)
			# update discriminator model weights
			d_loss2, _ = d_model.train_on_batch(X_fake, y_fake)
			# prepare points in latent space as input for the generator
			X_gan = generate_latent_points(latent_dim, n_batch)
			# create inverted labels for the fake samples
			y_gan = np.ones((n_batch, 1))
			# update the generator via the discriminator's error
			g_loss = gan_model.train_on_batch(X_gan, y_gan)
			# summarize loss on this batch
			print('>%d, %d/%d, d1=%.3f, d2=%.3f g=%.3f' %
				(i+1, j+1, bat_per_epo, d_loss1, d_loss2, g_loss))
	# save the generator model
	g_model.save('generator.h5')

def show_plot(examples, n):
	# plot images
	for i in range(n * n):
		# define subplot
		plt.subplot(n, n, 1 + i)
		# turn off axis
		plt.axis('off')
		# plot raw pixel data
		plt.imshow(examples[i, :, :, 0], cmap='gray_r')
	plt.show()

# # size of the latent space
# latent_dim = 100
# # create the discriminator
# discriminator = define_discriminator()
# # create the generator
# generator = define_generator(latent_dim)
# # create the gan
# gan_model = define_gan(generator, discriminator)
# # load image data
# dataset = load_real_samples()
# # train model
# train(generator, discriminator, gan_model, dataset, latent_dim)

model = keras.models.load_model('generator.h5')

# generate images
latent_points = generate_latent_points(100, 100)
# generate images
X = model.predict(latent_points)
# plot the result
show_plot(X, 10)