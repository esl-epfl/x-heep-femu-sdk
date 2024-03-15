import xml.dom.minidom


def get_address_map(bitstream="/home/xilinx/x-heep-femu-sdk/hw/x_heep.bit"):
    
    # Get the corresponding .hwh pair to the .bit file
    hwh_dir = bitstream[:-4] + ".hwh"
    
    # Read the .hwh file to parse
    hwh_file = xml.dom.minidom.parse(hwh_dir)

    try:
        # Get the node with MEMORYMAP, there are many on those, but they are all the same
        memory_map = hwh_file.getElementsByTagName("MEMORYMAP")[0] #same addresses are iteratively existent

        # Get each element
        memory_ranges = memory_map.getElementsByTagName("MEMRANGE")

        address_offset_map = dict()

        for a in range(len(memory_ranges)):
            address_offset_map[memory_ranges[a].getAttribute("INSTANCE")] = int(memory_ranges[a].getAttribute("BASEVALUE"), 16)

        return address_offset_map
    
    except:
        print("No AXI MMIO found!")