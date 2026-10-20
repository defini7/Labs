select r.route_id, r.station_from_id, r.station_to_id, r.avg_cost_rub, r.max_cars, opening_date from routes as r, stations
where
	stations.station_name = 'Дзержинск' and
	avg_cost_rub >= 15724
order by avg_cost_rub desc, route_id, station_from_id, station_to_id, opening_date, r.max_cars nulls last
limit 7