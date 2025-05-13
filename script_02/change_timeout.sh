#!/bin/bash
echo "#!/bin/bash" > script/find_hostname.sh
echo 'timeout '"$1"' fping -c1 "$1" 2>/dev/null | awk '"'"'{print $6}'"'" >> script/find_hostname.sh
