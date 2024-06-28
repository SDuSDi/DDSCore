import paho.mqtt.client as mqtt
import numpy as np
import matplotlib.pyplot as plt
import json
from mpl_toolkits.basemap import Basemap

class PipListener(mqtt.Client):

    def __init__(self, topic_, status_):
        super(PipListener, self).__init__(mqtt.CallbackAPIVersion.VERSION2, client_id="DDSCore-Illustrator", clean_session=status_)
        self.topic = topic_
        self.client_id = "DDSCore-Illustrator"
        self.lat = []
        self.lon = []
        self.map = Basemap(llcrnrlon=-100.,llcrnrlat=0.,urcrnrlon=-20.,urcrnrlat=57.,
            projection='lcc',lat_1=20.,lat_2=40.,lon_0=-60.,
            resolution ='l',area_thresh=1000.)

    def on_connect(self, mqttc, obj, flags, reason_code, properties):
        print("\nConnection sucess")
        print("\nSubscribing to topic '{0}'".format(self.topic))
        print("\tfor client ",self.client_id)

        self.subscribe(self.topic, 0)

    def on_connect_fail(self, mqttc, obj):
        print("\nConnection failed. Retrying...")

    def on_message(self, mqttc, obj, msg): #TODO: Message received

        j = json.loads(msg.payload)

        plt.title("Movement representation")
        plt.xlabel("Longitude")
        plt.ylabel("Latitude")

        if j["recipient"]=="-1":

            self.lat.append(j["lat"])
            self.lon.append(j["lon"])

            # self.map.plot(self.lat,self.lon,linewidth=1000,c='b')
            plt.scatter(self.lon,self.lat)
            plt.pause(0.05)

            #self.map.shadedrelief()
            #self.map.drawmapboundary(fill_color='#99ffff')
            #self.map.fillcontinents(color='#cc9966',lake_color='#99ffff')
            #self.map.drawparallels(np.arange(10,70,20),labels=[1,1,0,0])
            #self.map.drawmeridians(np.arange(-100,0,20),labels=[0,0,0,1])

            plt.draw()

    def on_subscribe(self, mqttc, obj, mid, reason_code_list, properties):
        print(self.client_id+" subscribed to topic {0}: ".format(self.topic)+str(mid)+" "+str(reason_code_list))

    # def on_log(self, mqttc, obj, level, string):
    #     print(string)

    def run(self):
        self.connect("127.0.0.1", 1883, 60)
        self.subscribe(self.topic, 0)

        self.loop_forever()

def main(args=None):

    mqttc = PipListener("MQTT-Status-Provider", False)
    mqttc.run()

if __name__ == '__main__':
    main()