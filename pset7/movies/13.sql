Select name
from people
where name != "Kevin Bacon"
    and id IN (
        select DISTINCT person_id
        from stars
        where movie_id IN (
                select movie_id
                from stars
                where person_id IN (
                        select id
                        from people
                        where name = "Kevin Bacon"
                            and birth = "1958"
                    )
            )
    );
