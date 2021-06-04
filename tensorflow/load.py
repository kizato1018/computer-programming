import tensorflow as tf
from tensorflow import keras
import numpy as np

def create_model():
    model = keras.Sequential([
        tf.keras.layers.Conv2D(32, (3,3), activation=tf.nn.relu, padding = "SAME", input_shape=(28, 28, 1)),
        tf.keras.layers.MaxPooling2D((2, 2), strides=2),
        tf.keras.layers.Conv2D(64, (3,3), activation=tf.nn.relu, padding = "SAME"),
        tf.keras.layers.MaxPooling2D((2, 2), strides=2),
        keras.layers.Flatten(),
        keras.layers.Dense(128, activation=tf.nn.relu),
        keras.layers.Dense(10)
    ])
    model.compile(optimizer='adam',
                loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                metrics=['accuracy'])
    return model

fashion_mnist = keras.datasets.fashion_mnist
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()
train_images, test_images = np.expand_dims(train_images, -1), np.expand_dims(test_images, -1)
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat',
               'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']
train_images = train_images / 255.0
test_images = test_images / 255.0

model = create_model()
model.load_weights('./checkpoint/fashion_checkpoint')

loss, acc = model.evaluate(test_images, test_labels, verbose=2)
print('\nTest accuracy:', acc)

new_model = keras.models.load_model('saved_model/fashion_model')
new_model.summary()

loss, acc = new_model.evaluate(test_images, test_labels, verbose=2)
print('\nTest accuracy:', acc)
# model.save('./saved_model/fashion_model')
