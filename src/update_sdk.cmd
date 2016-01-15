REM This script replaces the SDK folder with the latest bits from the Azure SDK repository.
REM It removes some files we do not need.  It currently targets the develop branch until fixes are
REM merged into master.

if exist "%~dp0\temp" rd /s /q "%~dp0\temp"
if exist "%~dp0\sdk" rd /s /q "%~dp0\sdk"

mkdir "%~dp0\temp"
mkdir "%~dp0\sdk"

cd /D "%~dp0\temp"

git clone -b develop https://github.com/Azure/azure-iot-sdks.git --recursive

cd "%~dp0\temp\azure-iot-sdks\"

git checkout develop

git reset --hard HEAD

git pull origin develop

cd "%~dp0\temp"

copy "%~dp0\temp\azure-iot-sdks\c\iothub_client\src\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\iothub_client\inc\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\serializer\src\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\serializer\inc\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\azure-c-shared-utility\c\src\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\azure-c-shared-utility\c\inc\" "%~dp0\sdk"
copy "%~dp0\temp\azure-iot-sdks\c\azure-c-shared-utility\c\adapters\agenttime.c" "%~dp0\sdk"

del "%~dp0\sdk\iot_logging.h"
del "%~dp0\sdk\iothubtransportamqp.*"
del "%~dp0\sdk\iothubtransportamqp_websockets.*"
del "%~dp0\sdk\iothubtransportmqtt.*"
del "%~dp0\sdk\tickcounter.*"
del "%~dp0\sdk\tlsio*.*"
del "%~dp0\sdk\constbuffer.*"

cd ..

rmdir /S "%~dp0\temp"
