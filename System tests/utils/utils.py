import sys
sikuli_jar_path = "C:\\Users\\mario\\Desktop\\Uni\\TFG\\Advanced-Clipboard\\System tests\\sikulixide-2.0.5.jar"

if sikuli_jar_path not in sys.path:
    sys.path.append(sikuli_jar_path)

from sikuli import *

app_exe_path = "C:\\Users\\mario\\Desktop\\Clipboard++-1.0.1-win64\\Clipboard++.exe - Acceso directo.lnk" #Needs to tbe edited for each system
app_name = "Clipboard++.exe" 

def before_each():
    script_path = getBundlePath() #This path will be from inside the tests folder
    images_path = script_path + "\\..\\..\\resources\\images" 
    addImagePath(images_path) #Add our own images location
    Settings.DefaultTimeout = 15 #Increase the default timeout

def create_img(imgPath):
    pattern = Pattern(imgPath)
    pattern.similar(0.85)
    return pattern

def open_clipboardXX():
    App.open(app_exe_path)
    wait(0.25)
    wait(create_img("ShortcutsView/ShortcutsView.png"))

def close_clipboardXX():
    click(create_img("External\TrayIcon.png"))
    wait(0.25)
    rightClick(create_img("External\Clipboard++TrayIcon.png"))
    wait(0.25) 
    click(create_img("External\CloseTrayIcon.png"))

def after_each():
    close_clipboardXX()