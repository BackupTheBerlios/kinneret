echo You must be root in order to copy files to /opt/kinneret
. mkdoc_he.sh
. mkdoc_en.sh
mkdir /opt/kinneret/l2swim/doc/he -p
mkdir /opt/kinneret/l2swim/doc/en -p
mkdir /opt/kinneret/l2swim/doc/image -p
mkdir /opt/kinneret/l2swim/etc -p
mkdir /opt/kinneret/images -p
cp ../doc/he/* /opt/kinneret/l2swim/doc/he -f
cp ../doc/en/* /opt/kinneret/l2swim/doc/en -f
cp ../doc/image/* /opt/kinneret/l2swim/doc/image -f
cp ../etc/*.txt /opt/kinneret/l2swim/etc -f
cp ../etc/image/* /opt/kinneret/images -f
