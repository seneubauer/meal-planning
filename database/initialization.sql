USE mealPlanning
GO

--------------------------------------------------
-->> enumeration tables
--------------------------------------------------

INSERT INTO mealPlanning.dbo.macronutrientType (name)
VALUES
('carbohydrate'),
('protein'),
('fat')

INSERT INTO mealPlanning.dbo.mealType (name)
VALUES
('breakfast'),
('lunch'),
('dinner'),
('snack'),
('dessert')

INSERT INTO mealPlanning.dbo.solubilityType (name)
VALUES
('water'),
('fat'),
('water & fat')

INSERT INTO mealPlanning.dbo.vitamin (name, alias, healthEffects, solubilityTypeID)
VALUES
('retinol', 'A', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'fat')),
('cholecalciferol', 'D', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'fat')),
('tocopherol', 'E', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'fat')),
('phylloquinone', 'K', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'fat')),
('thiamine', 'B1', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('riboflavin', 'B2', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('niacin', 'B3', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('pantothenic acid', 'B5', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('pyridoxine', 'B6', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('biotin', 'B7', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('folate', 'B9', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('cobalamin', 'B12', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water')),
('ascorbic acid', 'C', 'text', (SELECT x.solubilityTypeID FROM mealPlanning.dbo.solubilityType x WHERE x.name = 'water'))
