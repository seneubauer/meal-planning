USE mealPlanning
GO

--------------------------------------------------
-->> schema reset
--------------------------------------------------
IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'macronutrient')
DROP TABLE mealPlanning.dbo.macronutrient;
IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'vitamin')
DROP TABLE mealPlanning.dbo.vitamin;

--------------------------------------------------
-->> enumeration tables
--------------------------------------------------
CREATE TABLE mealPlanning.dbo.macronutrient (
	macronutrientID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(64) NOT NULL,
	alias VARCHAR(32) NOT NULL,
	CONSTRAINT uq_macronutrient_macronutrientID UNIQUE (macronutrientID),
	CONSTRAINT uq_macronutrient_name UNIQUE (name),
	CONSTRAINT pk_macronutrient PRIMARY KEY CLUSTERED (macronutrientID)
);
CREATE TABLE mealPlanning.dbo.vitamin (
	vitaminID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(64) NOT NULL,
	alias VARCHAR(32) NOT NULL,
	CONSTRAINT uq_vitamin_vitaminID UNIQUE (vitaminID),
	CONSTRAINT uq_vitamin_name UNIQUE (name),
	CONSTRAINT pk_vitamin PRIMARY KEY CLUSTERED (vitaminID)
);
CREATE TABLE mealPlanning.dbo.mealType (
	mealTypeID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(32) NOT NULL,
	CONSTRAINT uq_mealType_mealTypeID UNIQUE (mealTypeID),
	CONSTRAINT uq_mealType_name UNIQUE (name),
	CONSTRAINT pk_mealType PRIMARY KEY CLUSTERED (mealTypeID)
)

--------------------------------------------------
-->> operation tables
--------------------------------------------------
CREATE TABLE mealPlanning.dbo.person (
	personID INT IDENTITY(1, 1) NOT NULL,
	firstName VARCHAR(30) NOT NULL,
	middleName VARCHAR(30) NULL,
	lastName VARCHAR(30) NOT NULL,
)
