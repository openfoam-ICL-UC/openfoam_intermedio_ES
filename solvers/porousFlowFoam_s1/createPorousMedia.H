
// Define dictionary
IOdictionary microstructureProperties
(
    IOobject
    (
        "microstructureProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

// Read eps (porosity) value from the microstructureProperties directory in constant/
dimensionedScalar eps(microstructureProperties.lookup("eps"));
Info << eps << endl;

// Read tau (tortuosity) value from the microstructureProperties directory in constant/
dimensionedScalar tau(microstructureProperties.lookup("tau"));
Info << tau << endl;

scalar tauBrugg;// definir variable para utilizar correlacion
if (eps.value() == 1.0)
{
    tauBrugg = 1.0;// if porosity is 1 then there is no porous media and tau is set to any value, here one
}else
{
    tauBrugg = 1.0 / Foam::pow(eps.value(), 1.0/2.0);
}

// Read permeability value (kappa) from the microstructureProperties directory in constant/
dimensionedScalar kappa(microstructureProperties.lookup("kappa"));
Info << kappa << endl;

// Read mean fibre diameter value (df) from the microstructureProperties directory in constant/
dimensionedScalar df(microstructureProperties.lookup("df"));
Info << df << endl;

// Read Carman-Kozeny coefficient value (kCK) from the microstructureProperties directory in constant/
dimensionedScalar kCK(microstructureProperties.lookup("kCK"));
Info << kCK << endl;

// Read forchheimer coefficient (beta) value from the microstructureProperties directory in constant/
dimensionedScalar beta(microstructureProperties.lookup("beta"));
Info << beta << endl;

scalar perm;// definir una variable para utilizar una correlacion
if (eps.value()==1.0)
{
    perm = 1.0;// if porosity is 1 then there is no porous media and permeability is set to any value, here one, to avoid division by one
}else
{
    perm = Foam::pow(df.value(),2.0) * Foam::pow(eps.value(),3.0) /(16.0 * kCK.value() * Foam::pow((1.0 - eps.value()),2.0));
}
Info << perm << endl;

Info<< "Reading field pore Index (0 in channel, 1 in porous media)\n" << endl;
volScalarField poreIdx
(
    IOobject
    (
        "poreIdx",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar( "poreIdx", dimless, 0.0 )
);

Info<< "Reading porosity (1 in channel, eps = " << eps.value() << " in porous media)\n" << endl;
volScalarField porosity
(
     IOobject
     (
	"porosity",
	runTime.timeName(),
	mesh,
    IOobject::NO_READ,
	IOobject::AUTO_WRITE // NO_WRITE
     ),
     mesh,
     dimensionedScalar("porosity",dimless,1.0)
);

if (tau.value() == 0.0)
{
    Info<< "Reading tortuosity (1 in channel, calculated tortuosity = " << tauBrugg << " in porous media)\n" << endl;
}else
{
    Info<< "Reading tortuosity (1 in channel, tau = " << tau.value() << " in porous media)\n" << endl;
}
volScalarField tortuosity
(
     IOobject
     (
	"tortuosity",
	runTime.timeName(),
	mesh,
    IOobject::NO_READ,
	IOobject::AUTO_WRITE // NO_WRITE
     ),
     mesh,
     dimensionedScalar("tortuosity",dimless,1.0)
);

if (kappa.value() == 0.0)
{
    Info<< "Reading permeability (1 in channel, calculated permeability = " << perm << " in porous media)\n" << endl;
}else
{
    Info<< "Reading permeability (1 in channel, kappa = " << kappa.value() << " in porous media)\n" << endl;
}
volScalarField permeability
(
     IOobject
     (
	"permeability",
	runTime.timeName(),
	mesh,
    IOobject::NO_READ,
	IOobject::AUTO_WRITE // NO_WRITE
     ),
     mesh,
     dimensionedScalar("permeability",dimArea,1.0)
);

Info<< "Reading Forchheimer coefficient (1 in channel, beta = " << beta.value() << " in porous media)\n" << endl;
volScalarField forchheimerCoeff
(
    IOobject
    (
	"forchheimerCoeff",
	runTime.timeName(),
	mesh,
    IOobject::NO_READ,
	IOobject::AUTO_WRITE // NO_WRITE
    ),
    mesh,
    dimensionedScalar("forchheimerCoeff",dimless/dimLength,1.0)
);


// Extracting cell zone defining porous media location
const labelList& porousCells = mesh.cellZones()[0];

// Assigning values in porous media domain defined in toposetDict 
forAll(porousCells,i)
{
	porosity[porousCells[i]] = eps.value();
    if (eps.value() == 1.0)
    {
        poreIdx[porousCells[i]] = 0.0;// do nothing poreIdx should be zero everywhere if porosity is 1 everywhere
    } else
    {
        poreIdx[porousCells[i]] = 1.0;
    }
    
    if (tau.value() == 0.0)
    {
        tortuosity[porousCells[i]] = tauBrugg;
    } else
    {
        tortuosity[porousCells[i]] = tau.value();
    }

    if (kappa.value() == 0.0)
    {
        permeability[porousCells[i]] = perm;
    } else
    {
        permeability[porousCells[i]] = kappa.value();
    }
    
    if (eps.value() == 1.0)
    {
        forchheimerCoeff[porousCells[i]] = 1.0;// do nothing poreIdx should be zero everywhere if porosity is 1 everywhere
    } else
    {
        forchheimerCoeff[porousCells[i]] = beta.value();
    }
}

// Interpolating porosity to get values at cell faces
surfaceScalarField porosityFaces = fvc::interpolate(porosity);
