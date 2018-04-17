pathBrew=`brew config | grep HOMEBREW_REPOSITORY | cut -d : -f 2`
openAlpath=`find $pathBrew/Cellar/* -name "openal.pc"`
pkgConfPath="$pathBrew/lib/pkgconfig/openal.pc"
rm -f $pkgConfPath
cp $openAlpath $pkgConfPath
