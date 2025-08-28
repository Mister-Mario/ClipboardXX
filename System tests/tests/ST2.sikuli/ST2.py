import sys
import os

script_path = getBundlePath()

parent_path = os.path.abspath(os.path.join(script_path, "..\\.."))

if parent_path not in sys.path:
    sys.path.append(parent_path)

from utils import utils, navigation
export_file = "ST2_export.txt"
try:
    utils.set_up()
    navigation.go_to_main_window_from_shortcuts()
    #Load Memory cell 1
    click(utils.create_img("MainView\\MemoryCell1.png"))
    wait(0.25)
    type(utils.create_img("MainView\\MemoryCellInput.png"), "<h1>\"Hello & World\"</h1>\\n\\t")
    wait(0.25)
    click(utils.create_img("MainView\\LoadCell.png"))

    #Load Memory cell 3
    click(utils.create_img("MainView\\MemoryCell3.png"))
    wait(0.25)
    type(utils.create_img("MainView\\MemoryCellInput.png"), "Content cell 3")
    wait(0.25)
    click(utils.create_img("MainView\\LoadCell.png"))
    
    #Export file
    navigation.go_to_export()
    utils.export_file(export_file,".")

    if(not utils.compare_files(utils.get_test_files_path() + "\\ST2_export_expected.txt",
                               utils.get_test_files_path() + "\\" + export_file)):
        raise ValueError("Files are not the same")

    #Import file
    navigation.go_to_import()
    utils.import_file(export_file,".")

    #Expected Memory cell 1
    click(utils.create_img("MainView\\MemoryCell1.png"))
    wait(utils.create_img("ExpectedMemoryCell1.png"))

    #Expected Memory cell 3
    click(utils.create_img("MainView\\MemoryCell3.png"))
    wait(utils.create_img("ExpectedMemoryCell3.png"))

except Exception as e:
    print("Test Failed, capturing actual screen")
    print(e)
    ruta_captura = capture(SCREEN)
    print("Path of screen capture", ruta_captura)

finally:
    utils.tear_down()