# Python Corner Grocer Code

# Updates made by: Jacob M. Petrelle
# Date: 02/27/22

import re
import string
from typing import Dict

# Define function to read file and print each produce item and their frequency from the original file on separate lines 
def PrintProduceAndNumberList():
    # Print list header
    print("* All Purchased Produce with Frequency of Purchases *")
    print("-----------------------------------------------------")
    print()

    dictOfProduce = {} # Declare empty dictionary
    
    listOfPurchasedProduce = open("CS210_Project_Three_Input_File.txt", "r") # Open file
    for item in listOfPurchasedProduce: # Loop through file
        item = item.strip() # Remove newlines
        # Check if current item is already in dictOfProduce
        if item in dictOfProduce: 
            currentValue = dictOfProduce[item] # Get current item's value
            newValue = currentValue + 1 # Add 1 to current item's value
            dictOfProduce.update({item : newValue}) # Update current dictionary item value
        else:
            dictOfProduce[item] = 1 # Add new item and value to dictionary
    for item in dictOfProduce: # Loop through dictionary
        print(item,dictOfProduce[item]) # print each item and value
    listOfPurchasedProduce.close() # Close file
    
    # Print list closer
    print("-----------------------------------------------------")
    
    return 0 # Return to C++


# Define function to read file and return frequency of entered string
def PrintFrequencyOfProduceItem(produceItem):
    dictOfProduce = {} # Declare empty dictionary
    
    listOfPurchasedProduce = open("CS210_Project_Three_Input_File.txt", "r") # Open file
    for item in listOfPurchasedProduce: # Loop through file
        item = item.strip() # Remove newlines
        if item in dictOfProduce: # Check if current item is already in dictOfProduce
            currentValue = dictOfProduce[item] # Get current item's value
            newValue = currentValue + 1 # Add 1 to current item's value
            dictOfProduce.update({item : newValue}) # Update current dict value
        else:
            dictOfProduce[item] = 1 # Add new item and value to dictionary
    listOfPurchasedProduce.close() # Close file
    
    # Check if entered produceItem is in dictOfProduce
    if produceItem in dictOfProduce:
        return dictOfProduce[produceItem] # Return frequency to C++
    else:
        return 0 # Return 0 for no frequency of entered produceItem


# Define function to read a file, then create and write to a file
def WritingProduceAndNumberFile():
    dictOfProduce = {} # Declare empty dictionary
    
    produceAndNumberFile = open("frequency.dat", "w") # Create file to write to
    listOfPurchasedProduce = open("CS210_Project_Three_Input_File.txt", "r") # Open file
    for item in listOfPurchasedProduce: # Loop through file
        item = item.strip() # Remove newlines
        if item in dictOfProduce: # Check if current item is already in dictOfProduce
            currentValue = dictOfProduce[item] # Get current item's value
            newValue = currentValue + 1 # Add 1 to current item's value
            dictOfProduce.update({item : newValue}) # Update current dict value
        else:
            dictOfProduce[item] = 1 # Add new item and value to dictionary
    for item in dictOfProduce: # Loop through dictionary
        fileLine = [item, " ", str(dictOfProduce[item]), "\n"] # Create line for item and frequency pairs
        produceAndNumberFile.writelines(fileLine) # Write fileLine to file

    listOfPurchasedProduce.close() # Close file
    produceAndNumberFile.close() # Close file

