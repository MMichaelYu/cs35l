#!/usr/bin/python
import random, sys, locale
from optparse import OptionParser

class comm:
    def __init__(self, file):
        f = open(file, 'r')
        self.lines = f.readlines()
        f.close()

		
def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2 Outputs three columns that compare file1 and file2."""
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="hidefile1", default=False, help="hide unique elements in file 1")
    parser.add_option("-2", action="store_true", dest="hidefile2", default=False, help="hide unique elements in file 2")
    parser.add_option("-3", action="store_true", dest="hidematches", default=False, help="hide elements that appear in both file1 and file2")
    parser.add_option("-u", action="store_true", dest="unsortedfiles", default=False, help="deals with unsorted files")

    def prints(element, col):
        if col==1:
            if options.hidefile1==True:
                return
                
        elif col==2:
            if options.hidefile2==True:
                return
            if options.hidefile1==False:
                sys.stdout.write("\t")

        elif col==3:
            if options.hidematches==True:
                return
            if options.hidefile2==False:
                sys.stdout.write("\t")
            if options.hidefile1==False:
                sys.stdout.write("\t")

        sys.stdout.write(element+"\n")

    options, args = parser.parse_args(sys.argv[1:])
    if len(args) != 2:
        parser.error("wrong number of operands")
    input1 = args[0]
    input2 = args[1]
	
    if input1=="-":
        list1=list(sys.stdin.readlines())
    else:
        temp=comm(input1)
        list1=list(temp.lines)

    if input2=="-":
        list2=list(sys.stdin.readlines())
    else:
        temp=comm(input2)
        list2=list(temp.lines)

    dict1 = {}
    dict2 = {}

    for thing in list1:
        foo = thing.replace("\n","")
        if foo in dict1:
            dict1[foo]+=1
        else:
            dict1[foo]=1

    for thing in list2:
        foo = thing.replace("\n","")
        if foo in dict2:
            dict2[foo]+=1
        else:
            dict2[foo]=1

    if options.unsortedfiles==True:
        for thing in list1:
            foo=thing.replace("\n","")
            if dict1[foo]>0:
                if foo in dict2:
                    if dict2[foo]>0:
                        prints(foo,3)
                        dict2[foo]-=1
                    else:
                        prints(foo,1)
                        
                else:
                    prints(foo,1)
                        
                    dict1[foo]-=1
        
        for thing in list2:
            foo=thing.replace("\n","")
            if dict2[foo]>0:
                if foo in dict1:
                    if dict1[foo]>0:
                        prints(foo,3)
                        dict1[foo]-=1
                    else:
                        prints(foo,2)

                else:
                    prints(foo,2)
            
                    dict2[foo]-=1
    else:
        combinedlist=list1+list2
        combinedlist.sort()
        for thing in combinedlist:
            foo=thing.replace("\n","")
            if foo in dict1 and dict1[foo]>0:
                if foo in dict2 and dict2[foo]>0:
                    prints(foo,3)
                    dict1[foo]-=1
                    dict2[foo]-=1
                else:
                    prints(foo,1)
                    dict1[foo]-=1
            elif foo in dict2 and dict2[foo]>0:
                prints(foo,2)
                dict2[foo]-=1

if __name__ == "__main__":
    main()
