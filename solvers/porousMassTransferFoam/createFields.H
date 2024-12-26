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


#include "createMRF.H"
#include "createFvOptions.H"

// Esquema de interpolación de superficie
multivariateSurfaceInterpolationScheme<scalar>::fieldTable fields;

// Puntero a objeto de la clase CombustionModel
autoPtr<CombustionModel<psiReactionThermo>> reaction
(
    CombustionModel<psiReactionThermo>::New(thermo, turbulence_mass())
);

// Info<< "Reading kinematic viscosity\n" << endl;
// volScalarField kinematicViscosity
// (
//     IOobject
//     (
// 	"kinematicViscosity",
// 	runTime.timeName(),
// 	mesh,
//     IOobject::NO_READ,
// 	IOobject::AUTO_WRITE // NO_WRITE
//     ),
//     mesh,
//     dimensionedScalar("kinematicViscosity",dimViscosity,nu.value())
//     // dimensionedScalar("kinematicViscosity",dimViscosity,1.0)
// );
 