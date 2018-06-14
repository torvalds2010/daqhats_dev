#!/usr/bin/env python
#
# MCC 118 example program
# Read and display analog input values
#
import sys
import daqhats as hats

# get hat list of MCC HAT boards
list = hats.hat_list(filter_by_id = hats.HatIDs.ANY)
if not list:
    print("No boards found")
    sys.exit()

# Read and display every channel
for entry in list: 
    
    if entry['id'] == hats.HatIDs.MCC_118:
        print("Board {}: MCC 118".format(entry['address']))
        board = hats.mcc118(entry['address'])
        for channel in range(board.a_in_num_channels()):
            value = board.a_in_read(channel)
            print("  Ch {0}: {1:.3f}".format(channel, value))
            