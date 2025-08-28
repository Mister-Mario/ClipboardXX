import sys
import os

from paths import *
sikuli_jar_path = get_sikulix_jar_path()
if sikuli_jar_path not in sys.path:
    sys.path.append(sikuli_jar_path)

from sikuli import *

script_path = getBundlePath() #This path will be from inside the tests folder
test_files_path = script_path + "\\..\\..\\resources\\files"
shortcuts_path = get_shortcuts_path()

def get_test_files_path():
    return test_files_path

def intialize_sikulix():
    images_path = script_path + "\\..\\..\\resources\\images" 
    addImagePath(images_path) #Add our own images location
    Settings.DefaultTimeout = 15 #Increase the default timeout

def create_img(imgPath):
    pattern = Pattern(imgPath)
    pattern.similar(0.85)
    return pattern

def open_clipboardXX():
    try:
        App.open(get_app_exe_path())
        wait(0.25)
        wait(create_img("ShortcutsView\\ShortcutsView.png"))
    except Exception as e:
        print("Set up error: ", e)

def close_clipboardXX():
    click(create_img("External\\TrayIcon.png"))
    wait(0.25)
    rightClick(create_img("External\\Clipboard++TrayIcon.png"))
    wait(0.25) 
    click(create_img("External\\CloseTrayIcon.png"))

def delete_file(my_file):
    if os.path.isfile(my_file):
        os.remove(my_file)
    else:
        print("Error deleting: ", my_file)

def restore_shortcuts():
    base_shortcuts = None
    user_shortcuts = None
    
    try:
        base_shortcuts = open(shortcuts_path + "\\shortCutsBase.csv", 'r')
        user_shortcuts = open(shortcuts_path + "\\shortCuts.csv", 'w')
        
        for linea in base_shortcuts:
            user_shortcuts.write(linea)
            
        print("Shortcuts restored")

    except Exception as e:
        print("Error while restoring shortcuts")
        print(e)

    finally:
        if base_shortcuts:
            base_shortcuts.close()
        if user_shortcuts:
            user_shortcuts.close()

def restore_blank():
    blank = None
    
    try:
        blank = open(test_files_path + "\\Blank.txt", 'w')#When opening with write we will empty the file
        
        print("Blank emptied restored")

    except Exception:
        print("Error while emptying")

    finally:
        if blank:
            blank.close()

def restore_existent_files():
    restore_shortcuts()
    restore_blank()

def delete_new_files():
    delete_file(test_files_path + "\\ST2_export.txt")
    delete_file(test_files_path + "\\ST3_1_export.txt")
    delete_file(test_files_path + "\\ST3_2_export.txt")
    delete_file(test_files_path + "\\ST4_export.txt")
    delete_file(test_files_path + "\\ST5_export.txt")
    delete_file(test_files_path + "\\ST6_export.txt")

def set_up():
    print("Starting test")
    intialize_sikulix()
    paste("")#Clear system's clipboard
    open_clipboardXX()

def tear_down():
    close_clipboardXX()
    restore_existent_files()
    delete_new_files()
    print("Finished test")


def export_file(file_name, separator):
    click(create_img("Export&ImportView\\SearchButton.png"))
    wait(create_img("Export&ImportView\\SearchView.png"))
    type(Key.BACKSPACE) #There is a base name
    wait(0.1)
    type(test_files_path +  "\\" + file_name)
    click(create_img("Export&ImportView\\SaveFileButton.png"))
    type(create_img("Export&ImportView\\Separator.png"), separator)
    click(create_img("Export&ImportView\\ConfirmButton.png"))
    wait(create_img("Export&ImportView\\CorrectExport.png"))
    click(create_img("Export&ImportView\\CorrectMsgButton.png"))

def import_file(file_name, separator):
    click(create_img("Export&ImportView\\SearchButton.png"))
    wait(create_img("Export&ImportView\\SearchView.png"))
    type(test_files_path +  "\\" + file_name)
    click(create_img("Export&ImportView\\OpenFileButton.png"))
    type(create_img("Export&ImportView\\Separator.png"), separator)
    click(create_img("Export&ImportView\\ConfirmButton.png"))
    wait(create_img("Export&ImportView\\CorrectImport.png"))
    click(create_img("Export&ImportView\\CorrectMsgButton.png"))

def compare_files(file_path_1, file_path_2):
    try:
        with open(file_path_1, 'r') as f1, open(file_path_2, 'r') as f2:
            return f1.readlines() == f2.readlines() #Can compare directly cause the expected file lenght is just 1 line
    except FileNotFoundError:
        return False