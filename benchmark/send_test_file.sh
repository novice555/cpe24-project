#!/bin/bash
#scp -P22222 diff_script.sh root@192.168.1.11:/koppae01/
#scp -P22222 diff_script.sh root@192.168.1.12:/koppae02/
#scp -P22222 diff_script.sh root@192.168.1.13:/koppae03/
#scp -P22222 diff_script.sh root@192.168.1.14:/koppae04/
scp -P22222 test.input root@192.168.1.11:/koppae01/
scp -P22222 test.input root@192.168.1.12:/koppae02/
scp -P22222 test.input root@192.168.1.13:/koppae03/
scp -P22222 test.input root@192.168.1.14:/koppae04/


#scp -P22222 diff_script.sh root@192.168.1.11:/koppae01_alone
#scp -P22222 test.input root@192.168.1.11:/koppae01_alone
