import xml.dom.minidom


def get_address_map(bitstream, verbose=False):

    # Get the corresponding .hwh pair to the .bit file
    hwh_dir = bitstream[:-4] + ".hwh"

    # Read the .hwh file to parse.
    hwh_file = xml.dom.minidom.parse(hwh_dir)

    try:
        # Obtain the memory mapped elements
        memory_maps = hwh_file.getElementsByTagName("MEMORYMAP")
        # Create a dictionary where to store the instances.
        address_offset_map = dict()
        for i in range(len(memory_maps)):
            # For each memory mapped blocked, the memory ranges will be analyzed.
            memory_map = memory_maps[i]
            memory_ranges = memory_map.getElementsByTagName("MEMRANGE")
            for a in range(len(memory_ranges)):
                # If one of the instances is not in the dictionary, add it.
                instance = memory_ranges[a].getAttribute("INSTANCE")
                if instance not in address_offset_map.keys():
                    val = int(memory_ranges[a].getAttribute("BASEVALUE"), 16)
                    if verbose: print(f"0x{val:08x}\t{instance}")
                    address_offset_map[memory_ranges[a].getAttribute("INSTANCE")] = int(memory_ranges[a].getAttribute("BASEVALUE"), 16)
        return address_offset_map

    except:
        print("No AXI MMIO found!")