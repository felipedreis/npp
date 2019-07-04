#!/bin/bash
curdir=`pwd`
cd .. 
tar -czf npp.tar npp/
scp -P2200 npp.tar felipe@cluster.decom.cefetmg.br:~/npp.tar
ssh -p2200 felipe@cluster.decom.cefetmg.br "tar -xzf npp.tar npp/"
cd $curdir


