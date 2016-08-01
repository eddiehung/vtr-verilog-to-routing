##############################################################################
# vtr-with-yosys
##############################################################################

This is a work-in-progress fork of VTR7.0 (at least what I think is [VTR7.0](https://github.com/eddiehung/vtr-with-yosys/releases/tag/vtr-7-i-think)!)
but supporting [Yosys](https://github.com/cliffordwolf/yosys) instead of ODIN_II as its front end.

This Yosys front-end plumbing was done as part of the [VTR-to-Bitstream V2.0](http://eddiehung.github.io/vtb.html) 
project, and was mostly taken from there, but without any of the destructive 
back-end mods I made for VPR to support Xilinx architectures.

Usage is:

```
./run_vtr_flow.pl ../benchmarks/verilog/diffeq1_yosys.v ../arch/timing/k6_frac_N10_frac_chain_mem32K_40nm.xml -yosys
```

Note the "`-yosys`" argument, plus the "`diffeq1_yosys.v`" benchmark, which is a
carbon-copy of the original ("`diffeq1.v`") but with a Verilog attribute `(* top *)`
attached to the top level module, and with any RTL changes necessary for Yosys
to support that circuit.

Currently, it's untested, and I can't promise I'll be able to support it.

---

This is the development trunk for the Verilog-to-Routing project.  Unlike the 
nicely packaged release that we create, you are working with code in a constant 
state of flux.  You should expect that the tools are not always stable and that 
more work is needed to get the flow to run.

For new developers, please do the tutorial in tutorial/NewDeveloperTutorial.txt.  You
will be directed back here once you ramp up.

Our work in VTR follows a classic svn workflow.  The trunk is supposed to be the 
most current stable version of the project.  Developers checkout a local copy of the code from the 
trunk at the start of development then do regular svn updates to keep in sync 
with the trunk.  When a developer has a tested, working change to put back into 
the trunk, he/she performs an "svn commit" operation.  Unstable code should
remain in the developer's local copy.

We do regular testing of the trunk using an automatic regression testing framework.  You
can see the state of the trunk here: http://canucks.eecg.toronto.edu:8080/waterfall

IMPORTANT:  Outside of special circumstance, a broken build must be fixed at top priority.  
You break the build if your commit breaks any of the automated regression tests.



##############################################################################
# Contributors (Please keep this up-to-date so that we can copy-paste into other locations)
##############################################################################

Professors: Kenneth Kent, Peter Jamieson, Jason Anderson, Vaughn Betz, Jonathan Rose

Graduate Students: Jason Luu, Jeffrey Goeders, Chi Wai Yu, Andrew Somerville, 
Ian Kuon, Alexander Marquardt, Andy Ye, Wei Mark Fang, Tim Liu, Charles Chiasson

Summer Students: Opal Densmore, Ted Campbell, Cong Wang, Peter Milankov, Scott Whitty, Michael Wainberg,
Suya Liu, Miad Nasr, Nooruddin Ahmed, Thien Yu, Long Yu Wang

Companies: Altera Corporation, Texas Instruments


