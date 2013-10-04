#!/usr/bin/env python
#
#==============================================================================#
# Import Modules                                                               #
#==============================================================================#

import sys, os, string, shutil

#outRoot ="Plots_El_0jets_chi4_mudist100_130930"
#outRoot ="Plots_Mu_0jets_chi4_mudist100_130930"
#outRoot ="Plots_El_4jets_top_chi4_mudist100_130930"
outRoot ="Plots_Mu_4jets_top_chi4_mudist100_130930"
#outRoot = "Skim_1lepton_1jpsi_130912"
exe = "./runMyAna"

#fileListDir = "filelists"
fileListDir = "filelists_skim_1lepton_1jpsi_130912"

mkdir="mkdir "+outRoot
os.system(mkdir)

copy = "cp MyAna.cc "+outRoot+"/"
os.system(copy)

filelist = os.popen("ls  "+fileListDir+"/*.list").readlines()

for aFile in filelist:
   
    outRoo1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".root"
    outLog1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".log"
    
    option  = " "
#    option  = " -skim"
    if aFile.count("SingleElectron") != 1 and aFile.count("SingleMu") != 1 and aFile.count("MuHad") != 1 and aFile.count("ElectronHad") != 1 :
        option = option+" -mc"

    if aFile.count("TTbar1") == 1:
        option = option+" -sig"    
        
    cmd = exe+" -filelist "+string.strip(aFile)+" -out "+outRoo1+" "+option+"  >&  "+outLog1 
    
    print cmd
    os.system(cmd)
    
sys.exit()
