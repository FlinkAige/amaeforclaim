con=amaeforclaim
tset $con $con

tcli set account permission $con active --add-code

admin=v1x.buy1

tpush amae.token  transfer '["ad", "'$con'", "100000.00000000 AMAE", "refuel"]' -p ad

tpush $con  claim '["joss", "ha22sh123", "100.00000000 AMAE", 0]' -p $admin

tpush $con  init '["v1x.buy1" ]' -p $con


tpush amae.token setacctperms '[ad,amaeforclaim,"8,AMAE",1,1]' -p ad