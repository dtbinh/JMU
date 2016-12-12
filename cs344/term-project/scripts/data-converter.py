#!/usr/bin/python
import io

def convert_data(file_name, dest_name):
    fp = open(file_name, "r")
    modified_csv = ""
    
    for row in fp.readlines():
        row_modified = row.replace("\r\n", "").split(",")

        # S1 Suit of Card 1 
        if row_modified[0] == "1":
            modified_csv += "0,0,0,1,"
        elif row_modified[0] == "2":
            modified_csv += "0,0,1,0,"
        elif row_modified[0] == "3":
            modified_csv += "0,1,0,0,"
        elif row_modified[0] == "4":
            modified_csv += "1,0,0,0,"
        else:
            modified_csv += "ERROR,ERROR,"

        # C1 Rank of card 1
        if row_modified[1] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,0,1,"
        elif row_modified[1] == "2":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,1,0,"
        elif row_modified[1] == "3":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,1,0,0,"
        elif row_modified[1] == "4":
            modified_csv += "0,0,0,0,0,0,0,0,0,1,0,0,0,"
        elif row_modified[1] == "5":
            modified_csv += "0,0,0,0,0,0,0,0,1,0,0,0,0,"
        elif row_modified[1] == "6":
            modified_csv += "0,0,0,0,0,0,0,1,0,0,0,0,0,"
        elif row_modified[1] == "7":
            modified_csv += "0,0,0,0,0,0,1,0,0,0,0,0,0,"
        elif row_modified[1] == "8":
            modified_csv += "0,0,0,0,0,1,0,0,0,0,0,0,0,"
        elif row_modified[1] == "9":
            modified_csv += "0,0,0,0,1,0,0,0,0,0,0,0,0,"
        elif row_modified[1] == "10":
            modified_csv += "0,0,0,1,0,0,0,0,0,0,0,0,0,"
        elif row_modified[1] == "11":
            modified_csv += "0,0,1,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[1] == "12":
            modified_csv += "0,1,0,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[1] == "13":
            modified_csv += "1,0,0,0,0,0,0,0,0,0,0,0,0,"
        else:
            "ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,"

        # S2 Suit of Card 2
        if row_modified[2] == "1":
            modified_csv += "0,0,0,1,"
        elif row_modified[2] == "2":
            modified_csv += "0,0,1,0,"
        elif row_modified[2] == "3":
            modified_csv += "0,1,0,0,"
        elif row_modified[2] == "4":
            modified_csv += "1,0,0,0,"
        else:
            modified_csv += "ERROR,ERROR,"

        # C2 Rank of card 2
        if row_modified[3] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,0,1,"
        elif row_modified[3] == "2":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,1,0,"
        elif row_modified[3] == "3":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,1,0,0,"
        elif row_modified[3] == "4":
            modified_csv += "0,0,0,0,0,0,0,0,0,1,0,0,0,"
        elif row_modified[3] == "5":
            modified_csv += "0,0,0,0,0,0,0,0,1,0,0,0,0,"
        elif row_modified[3] == "6":
            modified_csv += "0,0,0,0,0,0,0,1,0,0,0,0,0,"
        elif row_modified[3] == "7":
            modified_csv += "0,0,0,0,0,0,1,0,0,0,0,0,0,"
        elif row_modified[3] == "8":
            modified_csv += "0,0,0,0,0,1,0,0,0,0,0,0,0,"
        elif row_modified[3] == "9":
            modified_csv += "0,0,0,0,1,0,0,0,0,0,0,0,0,"
        elif row_modified[3] == "10":
            modified_csv += "0,0,0,1,0,0,0,0,0,0,0,0,0,"
        elif row_modified[3] == "11":
            modified_csv += "0,0,1,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[3] == "12":
            modified_csv += "0,1,0,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[3] == "13":
            modified_csv += "1,0,0,0,0,0,0,0,0,0,0,0,0,"
        else:
            "ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,"

        # S3 Suit of Card 3
        if row_modified[4] == "1":
            modified_csv += "0,0,0,1,"
        elif row_modified[4] == "2":
            modified_csv += "0,0,1,0,"
        elif row_modified[4] == "3":
            modified_csv += "0,1,0,0,"
        elif row_modified[4] == "4":
            modified_csv += "1,0,0,0,"
        else:
            modified_csv += "ERROR,ERROR,"

        # C3 Rank of card 3
        if row_modified[5] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,0,1,"
        elif row_modified[5] == "2":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,1,0,"
        elif row_modified[5] == "3":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,1,0,0,"
        elif row_modified[5] == "4":
            modified_csv += "0,0,0,0,0,0,0,0,0,1,0,0,0,"
        elif row_modified[5] == "5":
            modified_csv += "0,0,0,0,0,0,0,0,1,0,0,0,0,"
        elif row_modified[5] == "6":
            modified_csv += "0,0,0,0,0,0,0,1,0,0,0,0,0,"
        elif row_modified[5] == "7":
            modified_csv += "0,0,0,0,0,0,1,0,0,0,0,0,0,"
        elif row_modified[5] == "8":
            modified_csv += "0,0,0,0,0,1,0,0,0,0,0,0,0,"
        elif row_modified[5] == "9":
            modified_csv += "0,0,0,0,1,0,0,0,0,0,0,0,0,"
        elif row_modified[5] == "10":
            modified_csv += "0,0,0,1,0,0,0,0,0,0,0,0,0,"
        elif row_modified[5] == "11":
            modified_csv += "0,0,1,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[5] == "12":
            modified_csv += "0,1,0,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[5] == "13":
            modified_csv += "1,0,0,0,0,0,0,0,0,0,0,0,0,"
        else:
            "ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,"

        # S3 Suit of Card 4
        if row_modified[6] == "1":
            modified_csv += "0,0,0,1,"
        elif row_modified[6] == "2":
            modified_csv += "0,0,1,0,"
        elif row_modified[6] == "3":
            modified_csv += "0,1,0,0,"
        elif row_modified[6] == "4":
            modified_csv += "1,0,0,0,"
        else:
            modified_csv += "ERROR,ERROR,"

        # C3 Rank of card 4
        if row_modified[7] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,0,1,"
        elif row_modified[7] == "2":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,1,0,"
        elif row_modified[7] == "3":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,1,0,0,"
        elif row_modified[7] == "4":
            modified_csv += "0,0,0,0,0,0,0,0,0,1,0,0,0,"
        elif row_modified[7] == "5":
            modified_csv += "0,0,0,0,0,0,0,0,1,0,0,0,0,"
        elif row_modified[7] == "6":
            modified_csv += "0,0,0,0,0,0,0,1,0,0,0,0,0,"
        elif row_modified[7] == "7":
            modified_csv += "0,0,0,0,0,0,1,0,0,0,0,0,0,"
        elif row_modified[7] == "8":
            modified_csv += "0,0,0,0,0,1,0,0,0,0,0,0,0,"
        elif row_modified[7] == "9":
            modified_csv += "0,0,0,0,1,0,0,0,0,0,0,0,0,"
        elif row_modified[7] == "10":
            modified_csv += "0,0,0,1,0,0,0,0,0,0,0,0,0,"
        elif row_modified[7] == "11":
            modified_csv += "0,0,1,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[7] == "12":
            modified_csv += "0,1,0,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[7] == "13":
            modified_csv += "1,0,0,0,0,0,0,0,0,0,0,0,0,"
        else:
            "ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,"

        # S3 Suit of Card 5
        if row_modified[8] == "1":
            modified_csv += "0,0,0,1,"
        elif row_modified[8] == "2":
            modified_csv += "0,0,1,0,"
        elif row_modified[8] == "3":
            modified_csv += "0,1,0,0,"
        elif row_modified[8] == "4":
            modified_csv += "1,0,0,0,"
        else:
            modified_csv += "ERROR,ERROR,"

        # C3 Rank of card 5
        if row_modified[9] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,0,1,"
        elif row_modified[9] == "2":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,0,1,0,"
        elif row_modified[9] == "3":
            modified_csv += "0,0,0,0,0,0,0,0,0,0,1,0,0,"
        elif row_modified[9] == "4":
            modified_csv += "0,0,0,0,0,0,0,0,0,1,0,0,0,"
        elif row_modified[9] == "5":
            modified_csv += "0,0,0,0,0,0,0,0,1,0,0,0,0,"
        elif row_modified[9] == "6":
            modified_csv += "0,0,0,0,0,0,0,1,0,0,0,0,0,"
        elif row_modified[9] == "7":
            modified_csv += "0,0,0,0,0,0,1,0,0,0,0,0,0,"
        elif row_modified[9] == "8":
            modified_csv += "0,0,0,0,0,1,0,0,0,0,0,0,0,"
        elif row_modified[9] == "9":
            modified_csv += "0,0,0,0,1,0,0,0,0,0,0,0,0,"
        elif row_modified[9] == "10":
            modified_csv += "0,0,0,1,0,0,0,0,0,0,0,0,0,"
        elif row_modified[9] == "11":
            modified_csv += "0,0,1,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[9] == "12":
            modified_csv += "0,1,0,0,0,0,0,0,0,0,0,0,0,"
        elif row_modified[9] == "13":
            modified_csv += "1,0,0,0,0,0,0,0,0,0,0,0,0,"
        else:
            "ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,ERROR,"
        
        # Class Poker Hand
        if row_modified[10] == "0":
            modified_csv += "0,0,0,0,0,0,0,0,0,1\r\n"
        elif row_modified[10] == "1":
            modified_csv += "0,0,0,0,0,0,0,0,1,0\r\n"
        elif row_modified[10] == "2":
            modified_csv += "0,0,0,0,0,0,0,1,0,0\r\n"
        elif row_modified[10] == "3":
            modified_csv += "0,0,0,0,0,0,1,0,0,0\r\n"
        elif row_modified[10] == "4":
            modified_csv += "0,0,0,0,0,1,0,0,0,0\r\n"
        elif row_modified[10] == "5":
            modified_csv += "0,0,0,0,1,0,0,0,0,0\r\n"
        elif row_modified[10] == "6":
            modified_csv += "0,0,0,1,0,0,0,0,0,0\r\n"
        elif row_modified[10] == "7":
            modified_csv += "0,0,1,0,0,0,0,0,0,0\r\n"
        elif row_modified[10] == "8":
            modified_csv += "0,1,0,0,0,0,0,0,0,0\r\n"
        elif row_modified[10] == "9":
            modified_csv += "1,0,0,0,0,0,0,0,0,0\r\n"
        else:
            modified_csv += "ERROR,ERROR,ERROR,ERROR\r\n"
    
    fn = open(dest_name, "w+")
    fn.write("S1.4,S1.3,S1.2,S1.1,C1.13,C1.12,C1.11,C1.10,C1.9,C1.8,C1.7,C1.6,C1.5,C1.4,C1.3,C1.2,C1.1,S2.4,S2.3,S2.2,S2.1,C2.13,C2.12,C2.11,C2.10,C2.9,C2.8,C2.7,C2.6,C2.5,C2.4,C2.3,C2.2,C2.1,S3.4,S3.3,S3.2,S3.1,C3.13,C3.12,C3.11,C3.10,C3.9,C3.8,C3.7,C3.6,C3.5,C3.4,C3.3,C3.2,C3.1,S4.4,S4.3,S4.2,S4.1,C4.13,C4.12,C4.11,C4.10,C4.9,C4.8,C4.7,C4.6,C4.5,C4.4,C4.3,C4.2,C4.1,S5.4,S5.3,S5.2,S5.1,C5.13,C5.12,C5.11,C5.10,C5.9,C5.8,C5.7,C5.6,C5.5,C5.4,C5.3,C5.2,C5.1,CLASS.10,CLASS.9,CLASS.8,CLASS.7,CLASS.6,CLASS.5,CLASS.4,CLASS.3,CLASS.2,CLASS.1\r\n")
    
    fn.write(modified_csv)

    fp.close()
    fn.close()

if __name__ == "__main__":
    convert_data("../original-data/poker-hand-testing.data", "../csv/testing-big.csv")
    convert_data("../original-data/poker-hand-training-true.data", "../csv/training-big.csv")
