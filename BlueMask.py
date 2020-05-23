#Python code for color detection
import cv2
import sys
import numpy as np 


cap=cv2.VideoCapture(0)

while(1):
   _,frame = cap.read()   
   hsv=cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
   lower_blue=np.array([110,50,50])
   upper_blue=np.array([130,255,255])
   mask=cv2.inRange(hsv,lower_blue,upper_blue)
   res=cv2.bitwise_and(frame,frame,mask= mask)
   cv2.imshow('frame',frame)
   cv2.imshow('mask',mask)
   cv2.imshow('res',res)
   if cv2.waitKey(5) & 0xFF ==ord('q'):
     break

cap.release()
cv2.destroyAllWindows()





