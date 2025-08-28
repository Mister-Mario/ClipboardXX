import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import utils, navigation
try:
    utils.set_up()
    navigation.go_to_main_window_from_shortcuts()
    #Load to memory cell 1 Hello
    click(utils.create_img("MainView\\MemoryCell1.png"))

    memory_cell_1_region = find(utils.create_img("EditLoadMemoryCell1Button.png"))
    click(memory_cell_1_region.center.offset(188, 0))

    wait(utils.create_img("EditView\\MemoryCell1CopyEdit.png"))
    type("j")
    type("c")
    click(utils.create_img("EditView\\ConfirmButton.png"))
    wait(utils.create_img("MemoryCell1CopyEdited.png"))

    App.open(utils.get_test_files_path() + "\\LoremIpsum.txt")
    wait(1)#Cannot tell which text editor will be used
    
    #Select Lorem word and copy
    doubleClick(utils.create_img("External\\LoremWord.png"))
    wait(1)
    navigation.bring_forward_shortcut()
    
    type("j")
    type("c")
    
    click()#Deselects word
    App(paths.get_text_editor_name()).closeByKey()
    

    #Export file
    navigation.bring_forward_tray_icon()
    navigation.go_to_main_window_from_shortcuts()
    navigation.go_to_export()
    utils.export_file("ST6_export.txt",".")

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST4_1_export_expected.txt",
                            utils.get_test_files_path() + "\\ST6_export.txt")):
        raise ValueError("Files are not the same")

except Exception:
    print("Test Failed, capturing actual screen")
    ruta_captura = capture(SCREEN)
    print("Path of screen capture", ruta_captura)

finally:
    utils.tear_down()