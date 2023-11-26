CREATE TABLE `animal_device` (
  `id_animal` int(11) NOT NULL,
  `id_device` int(11) NOT NULL,
  PRIMARY KEY (`id_animal`,`id_device`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8
