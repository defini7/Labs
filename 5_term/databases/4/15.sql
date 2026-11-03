select distinct route_id from routes
except select route_id from route_repairs
order by route_id

select distinct route_id from route_repairs
except select route_id from route_repairs
order by route_id