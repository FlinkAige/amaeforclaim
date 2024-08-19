mpush amax.mtoken issue '["armoniaadmin","7000000.000000 MUSDT",""]' -p armoniaadmin
mtran -c amax.mtoken armoniaadmin amaeforclaim "7000000.400000 MUSDT" "refuel"
mtbl amax.mtoken MUSDT stat

#Oct-28-2022
mpush amax.mtoken issue '["armoniaadmin","4000000.000000 MUSDT",""]' -p armoniaadmin
mtran -c amax.mtoken armoniaadmin amaeforclaim "4000000.000000 MUSDT" "refuel"
mtbl amax.mtoken MUSDT stat