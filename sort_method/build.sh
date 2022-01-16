##########################################################################
# File Name: build.sh
# Author: JianWei
# mail: wj_clear@163.com
# Created Time: 2022年01月16日 星期日 15时57分09秒
#########################################################################
#!/bin/bash
PATH=/home/edison/bin:/home/edison/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin
export PATH

make clean; make -j
