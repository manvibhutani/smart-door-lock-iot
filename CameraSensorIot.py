import cv2
import requests
import time
import face_recognition 
from simple_facerec import SimpleFacerec 
sfr=SimpleFacerec()

sfr.load_encoding_images("images/")
doorOpen="https://blr1.blynk.cloud/external/api/update?token=v9xcyp1BvnqLcdLx7F3q7BgugEaZYjXr&v0=1"     
doorClosed="https://blr1.blynk.cloud/external/api/update?token=v9xcyp1BvnqLcdLx7F3q7BgugEaZYjXr&v0=2"
defaultDoor="https://blr1.blynk.cloud/external/api/update?token=v9xcyp1BvnqLcdLx7F3q7BgugEaZYjXr&v0=0"
  
cap=cv2.VideoCapture(0)
unknown_detected=False
requests.get(defaultDoor) 
while True:
    ret,frame = cap.read()
    face_locations,face_names=sfr.detect_known_faces(frame)
    for face_loc,name in zip(face_locations, face_names):
        y1,x1,y2,x2=face_loc[0],face_loc[1],face_loc[2],face_loc[3]
        cv2.putText(frame,name,((x2+60),(y1-10)),cv2.FONT_HERSHEY_COMPLEX,1,(0,0,0),2)
        cv2.rectangle(frame,(x1,y1),(x2,y2),(0,0,200),2)
        if name=="Unknown":
            unknown_detected=True
        else:
            unknown_detected=False
            
            
            
    if unknown_detected:
      requests.get(doorClosed)
      time.sleep(2)
      break
    else:
        requests.get(doorOpen)
        
        
     

    cv2.imshow("Smart Door Lock",frame)
    key=cv2.waitKey(1)
    
    if key==27:
        break

cap.release()
cv2.destroyAllWindows()