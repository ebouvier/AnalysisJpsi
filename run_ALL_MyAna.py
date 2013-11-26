#!/usr/bin/env python
#
#==============================================================================#
# Import Modules                                                               #
#==============================================================================#

import sys, os, string, shutil

#outRoot ="Plots_El_2jets40_3jets35_chi5_mudist105_drjet03_ctausup_131106"
#outRoot ="Plots_Mu_2jets40_3jets35_chi5_mudist105_drjet03_ctausup_131106"
outRoot ="Plots_El_2jets40_chi5_mudist105_drjet03_ctausup_131121"
#outRoot ="Plots_Mu_2jets40_chi5_mudist105_drjet03_ctausup_131121"
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
