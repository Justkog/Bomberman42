pathBrew=`brew config | grep HOMEBREW_REPOSITORY | cut -d : -f 2`
openAlpath=`find $pathBrew/Cellar/* -name "openal.pc"`
pkgConfPath="$pathBrew/lib/pkgconfig/openal.pc"
rm -f $pkgConfPath
cp $openAlpath $pkgConfPath
sndfile=`find $pathBrew/Cellar/libsndfile/1.0.28/lib/pkgconfig/sndfile.pc`
chmod 777 $sndfile
sed -i -e 's/libogg\/1.3.2/libogg\/1.3.3/g' $sndfile
sed -i -e 's/libvorbis\/1.3.5/libvorbis\/1.3.6/g' $sndfile
rm -rf tinyobjloader
git clone https://github.com/syoyo/tinyobjloader.git
rm -rf tinyobjloader/.git
rm -rf stb
git clone https://github.com/nothings/stb.git
rm -rf stb/.git
git clone https://github.com/supergrover/sigslot.git sources/sigslot
rm -rf sigslot/.git

