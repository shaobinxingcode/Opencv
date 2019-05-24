import argparse
import time
import imutils
import cv2

ap = argparse.ArgumentParser()
ap.add_argument("-v","--video")
# Minimal detect area size
ap.add_argument("-a","--min-area",type=int, default=1000)
args = vars(ap.parse_args())

if args.get("video") == None:
    # detect from camera
    camera = cv2.VideoCapture(0)
else:
    camera = cv2.VideoCapture(args["video"])

time.sleep(1)

firstRet, firstFrame = camera.read()

firstFrame = imutils.resize(firstFrame, width=1000)
gray_firstFrame = cv2.cvtColor(firstFrame, cv2.COLOR_BGR2GRAY)
firstFrame = cv2.GaussianBlur(gray_firstFrame, (21,21), 0)

p =0

while (1):
    (ret, frame) = camera.read()
    p +=1
    if not ret:
        break
    
    #initialize current frame to gray
    frame = imutils.resize(frame, width=1000)
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray_frame = cv2.GaussianBlur(gray_frame, (21,21), 0)

    frameDiff = cv2.absdiff(firstFrame, gray_frame)
    retVal, thresh = cv2.threshold(frameDiff, 25, 255, cv2.THRESH_BINARY)

    thresh = cv2.dilate(thresh, None, iterations=2)
    image, contours, hierarchy = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    text = "No Move Objects"
    for contour in contours:
        if cv2.contourArea(contour) < args["min_area"]:
            continue

        (x,y,w,h) = cv2.boundingRect(contour)
        cv2.rectangle(frame,(x,y),(x+w,y+h), (0,255,0), 2)
        text = "Object Moving"

    cv2.putText(frame, "Status: {}".format(text),(10,20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,0,255), 2)

    cv2.imshow('frame',frame)
    cv2.imshow('thresh',thresh)
    cv2.imshow('frameDiff', frameDiff)

print(p)
camera.release()


