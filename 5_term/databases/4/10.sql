WITH counts AS (
    SELECT 
        station_to_id, 
        COUNT(DISTINCT station_from_id) AS senders_count
    FROM orders
    GROUP BY station_to_id
),
ranked AS (
    SELECT 
        station_to_id, 
        senders_count,
        ROW_NUMBER() OVER (ORDER BY senders_count DESC, station_to_id ASC) AS rn_max,
        ROW_NUMBER() OVER (ORDER BY senders_count ASC, station_to_id ASC) AS rn_min
    FROM counts
)
SELECT 
    station_to_id, 
    senders_count,
    CASE 
        WHEN rn_max <= 4 AND rn_min <= 4 THEN 'макс./мин.'
        WHEN rn_max <= 4 THEN 'макс.'
        WHEN rn_min <= 4 THEN 'мин.'
    END AS mark
FROM ranked
WHERE rn_max <= 4 OR rn_min <= 4
ORDER BY 
    CASE WHEN rn_max <= 4 THEN 1 ELSE 2 END,
    senders_count DESC, 
    station_to_id ASC;