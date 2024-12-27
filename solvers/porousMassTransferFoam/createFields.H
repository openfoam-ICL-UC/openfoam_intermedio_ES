// Crea lista de punteros de fracciones másicas
autoPtr<psiReactionThermo> pThermo(psiReactionThermo::New(mesh)); 
psiReactionThermo& thermo = pThermo(); 
thermo.validate(args.executable(), "h", "e"); 
basicSpecieMixture& composition = thermo.composition(); 
PtrList<volScalarField>& Y = composition.Y(); 

// Crea word inertSpecie utilizada en createFieldsRefs.H
const word inertSpecie(thermo.get<word>("inertSpecie"));
if (!composition.species().found(inertSpecie))
{
    FatalIOErrorIn(args.executable().c_str(), thermo)
        << "Inert specie " << inertSpecie << " not found in available species "
        << composition.species() << exit(FatalIOError);
}

Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

// Crea R Delta T
#include "createRDeltaT.H"

Info<< "Reading field U \n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);



#include "createPhi.H"

label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, piso.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());

singlePhaseTransportModel laminarTransport(U, phi);
//read kinematic viscosity value (nu) from the transportProperties directory in constant/
dimensionedScalar nu("nu", dimViscosity, laminarTransport);

Info << "Creating incompressible turbulence model.\n" << nl;
autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh
    ),
    thermo.rho()
);

Info << "Creando modelo de turbulencia para transferencia de masa\n" << nl;
autoPtr<compressible::turbulenceModel> turbulence_mass
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        phi,
        thermo
    )
);



#include "createMRF.H"
#include "createFvOptions.H"

// Esquema de interpolación de superficie
multivariateSurfaceInterpolationScheme<scalar>::fieldTable fields;

// Agrega los campos de fracción másica y entalpía al esquema
// de interpolación

forAll(Y, i)
{
    fields.add(Y[i]);
}

fields.add(thermo.he());

// Puntero a objeto de la clase CombustionModel
autoPtr<CombustionModel<psiReactionThermo>> reaction
(
    CombustionModel<psiReactionThermo>::New(thermo, turbulence_mass())
);

volScalarField Qdot
(
    IOobject
    (
        "Qdot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimEnergy/dimVolume/dimTime, Zero)
);

// Densidad dimensional
dimensionedScalar rho_dim = dimensionedScalar("rho_dim", dimensionSet(1, -3, 0, 0, 0, 0, 0), 1);

// Número de Schmidt turbulento
dimensionedScalar Sct("Sct", dimless, laminarTransport);

// Difusividad molecular
dimensionedScalar D("D", dimensionSet(0, 2, -1, 0, 0, 0), laminarTransport);