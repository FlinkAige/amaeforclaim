# mpush amax.mtoken create '["armoniaadmin","1000000000000.000000 MUSDT"]' -pamax.mtoken

# mpush amax.mtoken issue '["armoniaadmin","1000000.000000 MUSDC","1st issue"]' -parmoniaadmin
# mtran -c amax.mtoken armoniaadmin amaeforclaim "1000000.000000 MUSDC" "refuel"

# mpush amaeforclaim addcoin '["6,MUSDC"]' -parmoniaadmin

# mpush amaeforclaim setaplfarm '["MUSDC","0.0500 APL",1]' -parmoniaadmin
# mpush amaeforclaim addchaincoin '["eth","6,MUSDC","5.000000 MUSDC"]' -p armoniaadmin
# mpush amaeforclaim addchaincoin '["tron","6,MUSDC","2.000000 MUSDC"]' -p armoniaadmin


mtbl amax.mtoken MUSDC stat