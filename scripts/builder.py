import os

if __name__ == "__main__":

    user = os.getlogin()
    if os.path.exists("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_config.yaml".format(user)):
        os.remove("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_config.yaml".format(user))
    if os.path.exists("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_deploy.yaml".format(user)):
        os.remove("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_deploy.yaml".format(user))

    replicas = int(input("Dame el número de réplicas que necesitas: "))

    config = open("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_config.yaml".format(user),"a")
    deploy = open("/home/{0}/ros2_ws/ddscore/scripts/k8s-builder-files/new_deploy.yaml".format(user),"a")

    deploy.writelines(["apiVersion: apps/v1\n","kind: Deployment\n","metadata:\n","  name: mosquitto\n","spec:\n","  replicas: 1\n","   selector:\n",
                       "    matchLabels:\n","      name: mosquitto\n","  template:\n","    metadata:\n","      labels:\n","        name: mosquitto\n","    spec:\n",
                       "      hostNetwork: true\n","      containers:\n","        - name: mosquitto\n","          image: eclipse-mosquitto:2.0.18\n",
                       "      imagePullPolicy: IfNotPresent\n","\n"])

    for i in range(0,replicas):

        config.writelines(["---\n","\n","apiVersion: v1\n","kind: ConfigMap\n","metadata:\n","  name: fastdds-config-domain-{0}\n".format(i),"  namespace: default\n",
                           "data:\n","  ROS_DOMAIN_ID: '{0}'\n".format(i),"  RMW_IMPLEMENTATION: rmw_fastrtps_cpp\n","  PX4_UXRCE_DDS_PORT: '{0}'\n".format(8000+i),"\n"])

        deploy.writelines(["---\n","\n","apiVersion: apps/v1\n","kind: Deployment\n","metadata:\n","  name: ddscore-{0}\n".format(i),"  labels:\n",
                           "    app: dds_l\n","spec:\n","  replicas: 1\n","  selector:\n","    matchLabels:\n","      app: dds_l\n","  template:\n","    metadata:\n",
                           "      labels:\n","        app: dds_l\n","    spec:\n","      hostNetwork: true\n","      containers:\n",
                           "      - name: ddscore-pod-{0}\n".format(i),"        image: local/ddscore:v1\n","        envFrom:\n","          - configMapRef:\n",
                           "              name: fastdds-config-domain-{0}\n".format(i),"\n"])
        
        deploy.writelines(["---\n","\n","apiVersion: apps/v1\n","kind: Deployment\n","metadata:\n","  name: px4-{0}\n".format(i),"  labels:\n",
                           "    app: px4_l\n","spec:\n","  replicas: 1\n","  selector:\n","    matchLabels:\n","      app: px4_l\n","  template:\n","    metadata:\n",
                           "      labels:\n","        app: px4_l\n","    spec:\n","      hostNetwork: true\n","      containers:\n","      - name: px4-pod-{0}\n".format(i),
                           "        image: local/px4:v1\n","        envFrom:\n","          - configMapRef:\n",
                           "              name: fastdds-config-domain-{0}\n".format(i),"\n"])

    config.close()
    deploy.close()