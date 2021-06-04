import tensorflow as tf
from tensorflow.python.client import device_lib

tf.__version__
tf.test.is_gpu_available()
tf.config.list_physical_devices('GPU')
print(device_lib.list_local_devices())