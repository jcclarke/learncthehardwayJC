# 1) Download it (use wget if you don't have curl)
curl -O https://sourceware.org/pub/valgrind/valgrind-3.15.0.tar.bz2

# use md5sum to make sure it matches the one on the site
md5sum valgrind-3.15.0.tar.bz2


# 2) Unpack it.
tar -xjvf valgrind-3.15.0.tar.bz2

#cd into the newly created directory
cd valgrind-3.15.0


# 3) configure it
./configure


# 4) make it
make


# 5) install it (need root)
sudo make install
