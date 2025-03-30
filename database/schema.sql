USE mealPlanning
GO

--------------------------------------------------
-->> schema reset
--------------------------------------------------

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'person')
DROP TABLE mealPlanning.dbo.person;

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'macronutrient')
DROP TABLE mealPlanning.dbo.macronutrient;

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'vitamin')
DROP TABLE mealPlanning.dbo.vitamin;

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'solubilityType')
DROP TABLE mealPlanning.dbo.solubilityType;

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'mealType')
DROP TABLE mealPlanning.dbo.mealType;

IF EXISTS(SELECT * FROM mealPlanning.INFORMATION_SCHEMA.TABLES x WHERE x.TABLE_SCHEMA = 'dbo' AND x.TABLE_NAME = 'macronutrientType')
DROP TABLE mealPlanning.dbo.macronutrientType;

--------------------------------------------------
-->> enumeration tables
--------------------------------------------------

CREATE TABLE mealPlanning.dbo.macronutrientType (
	macronutrientTypeID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(32) NOT NULL,
	CONSTRAINT uq_macronutrientType_macronutrientTypeID UNIQUE (macronutrientTypeID),
	CONSTRAINT uq_macronutrientType_name UNIQUE (name),
	CONSTRAINT pk_macronutrientType PRIMARY KEY CLUSTERED (macronutrientTypeID)
);

CREATE TABLE mealPlanning.dbo.mealType (
	mealTypeID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(32) NOT NULL,
	CONSTRAINT uq_mealType_mealTypeID UNIQUE (mealTypeID),
	CONSTRAINT uq_mealType_name UNIQUE (name),
	CONSTRAINT pk_mealType PRIMARY KEY CLUSTERED (mealTypeID)
);

CREATE TABLE mealPlanning.dbo.solubilityType (
	solubilityTypeID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(32) NOT NULL,
	CONSTRAINT uq_solubilityType_mealTypeID UNIQUE (solubilityTypeID),
	CONSTRAINT uq_solubilityType_name UNIQUE (name),
	CONSTRAINT pk_solubilityType PRIMARY KEY CLUSTERED (solubilityTypeID)
);

--------------------------------------------------
-->> operation tables
--------------------------------------------------

CREATE TABLE mealPlanning.dbo.vitamin (
	vitaminID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(64) NOT NULL,
	alias VARCHAR(32) NOT NULL,
	healthEffects VARCHAR(5000) NULL,
	solubilityTypeID INT NOT NULL,
	CONSTRAINT fk_vitamin_solubilityTypeID FOREIGN KEY (solubilityTypeID) REFERENCES mealPlanning.dbo.solubilityType (solubilityTypeID),
	CONSTRAINT uq_vitamin_vitaminID UNIQUE (vitaminID),
	CONSTRAINT uq_vitamin_name UNIQUE (name),
	CONSTRAINT pk_vitamin PRIMARY KEY CLUSTERED (vitaminID)
);

CREATE TABLE mealPlanning.dbo.macronutrient (
	macronutrientID INT IDENTITY(1, 1) NOT NULL,
	name VARCHAR(64) NOT NULL,
	alias VARCHAR(32) NOT NULL,
	macronutrientTypeID INT NOT NULL,
	CONSTRAINT fk_macronutrient_macronutrientTypeID FOREIGN KEY (macronutrientTypeID) REFERENCES mealPlanning.dbo.macronutrientType (macronutrientTypeID),
	CONSTRAINT uq_macronutrient_macronutrientID UNIQUE (macronutrientID),
	CONSTRAINT uq_macronutrient_name UNIQUE (name),
	CONSTRAINT pk_macronutrient PRIMARY KEY CLUSTERED (macronutrientID)
);

CREATE TABLE mealPlanning.dbo.person (
	personID INT IDENTITY(1, 1) NOT NULL,
	firstName VARCHAR(30) NOT NULL,
	middleName VARCHAR(30) NULL,
	lastName VARCHAR(30) NOT NULL,
);
