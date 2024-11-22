from secrets import DEVICE_ID
from secrets import SECRET_KEY
from arduino_iot_cloud import ArduinoCloudClient
import time

client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY, sync_mode=True)
client.register("python_integer_test", value=1)
client.start()
time_update = time.time()

while True:
    client.update()
    time.sleep(0.01)
    if time.time() - time_update >= 1:
        time_update = time.time()
        client["python_integer_test"] += 1

