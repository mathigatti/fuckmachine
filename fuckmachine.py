
import RPi.GPIO as GPIO          
import argparse

from pythonosc.dispatcher import Dispatcher
from pythonosc import osc_server

def toggle_handler(unused_addr, args, volume):
    print(f"{args[0]}: {volume}")
    if volume == 0:
        stop()
    else:
        start()

def slider_handler(unused_addr, args, volume):
    volume = int(volume*100)
    volume = int(volume*100)
    motor_speed()
    print(f"{args[0]}: {volume}")

def motor_speed(speed=10):
    p.ChangeDutyCycle(speed)

def stop():
    GPIO.output(in1,GPIO.LOW)
    GPIO.output(in2,GPIO.LOW)
  
def start():
    GPIO.output(in1,GPIO.HIGH)
    GPIO.output(in2,GPIO.LOW)

in1 = 24
in2 = 23
en = 25
temp1=1

GPIO.setmode(GPIO.BCM)
GPIO.setup(in1,GPIO.OUT)
GPIO.setup(in2,GPIO.OUT)
GPIO.setup(en,GPIO.OUT)
GPIO.output(in1,GPIO.LOW)
GPIO.output(in2,GPIO.LOW)
p=GPIO.PWM(en,1000)

p.start(10)

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("--ip",
      default="0.0.0.0", help="The ip to listen on")
  parser.add_argument("--port",
      type=int, default=10000, help="The port to listen on")
  args = parser.parse_args()

  dispatcher = Dispatcher()
  dispatcher.map("/oscControl/toggle1", toggle_handler, "on/off")
  dispatcher.map("/oscControl/slider1", slider_handler, "Speed")

  server = osc_server.ThreadingOSCUDPServer(
      (args.ip, args.port), dispatcher)
  print("Serving on {}".format(server.server_address))
  server.serve_forever()