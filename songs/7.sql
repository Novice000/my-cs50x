SELECT avg(songs.energy) FROM songs JOIN artists ON songs.artist_id = artists.id where artists.name = 'Drake';
