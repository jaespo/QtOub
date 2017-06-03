create table user ( 
	username		varchar(32) not null, 
	password		varchar(32) not null,
	constraint pk_name primary key ( monname )
);

create table monster( 
	monname			varchar(32) not null, 
	montype			varchar(32) not null,
	offence			smallint not null,
	defence			smallint not null,
	rarity			smallint not null,
	special			varchar(32),
	constraint pk_name primary key ( monname )
);

create table deck( 
	username			varchar(32) not null,
	deckname			varchar(32) not null,
	constraint pk_username_deckname primary key ( username, deckname )
);

create table deck_monster( 
	username			varchar(32) not null,
	deckname			varchar(32) not null,
	cardix				smallint not null,
	monname				varchar(32) not null,
	constraint pk_username_deckname_cardix primary key ( username, deckname, cardix )
);

create table zoo( 
	username			varchar(32) not null,
	monname				varchar(32) not null,
	number				smallint not null,
	constraint pk_username_monname primary key ( username, deckname )
);

