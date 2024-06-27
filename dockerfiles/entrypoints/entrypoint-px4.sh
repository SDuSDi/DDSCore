#! /bin/bash
set -e

# if [ $PX4_UXRCE_DDS_PORT -eq 8001 ] 
# then 
#     cd PX4-Autopilot/ROMFS/px4fmu_common/init.d-posix
#     sed -i "/uxrce_dds_client start/d" rcS
#     cd
# fi

cd PX4-Autopilot && HEADLESS=1 make px4_sitl gz_x500