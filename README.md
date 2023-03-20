# Mongoose OS Multi-core experiments

A small toy example to test how Mongoose OS affects FreeRTOS tasks running on different cores. Adapted from the example found here: https://community.mongoose-os.com/t/here-is-a-freertos-example/945

Build using `mos build --platform esp32`.

Flash using `mos flash --esp32-encryption-key-file <ENCRYPTION_KEY_FILE>.key --port <COMX>`.
