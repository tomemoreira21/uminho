-- DROP USERS

 -- DROP USER IF EXISTS 
--  'anselmo'@'localhost',
--  'carlos'@'localhost',
--  'cristina'@'localhost';

-- DROP ROLES
-- DROP ROLE IF EXISTS administrador, operador;


CREATE ROLE administrador, operador;



GRANT SELECT, INSERT, UPDATE, DELETE
ON DigiTrip.Viajante
TO administrador WITH GRANT OPTION;

GRANT SELECT, INSERT, UPDATE, DELETE
ON DigiTrip.Idiomas
TO administrador WITH GRANT OPTION;


GRANT SELECT
ON DigiTrip.Viajante
TO operador;

GRANT DELETE, SELECT
ON DigiTrip.Comentario
TO operador;


CREATE USER 'anselmo'@'localhost' IDENTIFIED BY 'anselmosilva';
CREATE USER 'carlos'@'localhost' IDENTIFIED BY 'carlosribeiro';
CREATE USER 'cristina'@'localhost' IDENTIFIED BY 'cristinaferreira';

-- atribuição roles
GRANT administrador TO 'anselmo'@'localhost';
SET DEFAULT ROLE administrador TO 'anselmo'@'localhost';

GRANT operador TO 'carlos'@'localhost';
SET DEFAULT ROLE operador TO 'carlos'@'localhost';

GRANT operador TO 'cristina'@'localhost';
SET DEFAULT ROLE operador TO 'cristina'@'localhost';

