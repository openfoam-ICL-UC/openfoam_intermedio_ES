// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

// Info << porosity << endl;
// Info << kinematicViscosity << endl;
// Info << permeability << endl;
// Info << forchheimerCoeff << endl;

fvVectorMatrix UEqn
(
   (1.0/porosity)*fvm::ddt(U) + fvm::div((phi/pow(porosityFaces,2)), U)
  // The mesh is fixed so we don't need the moving reference frame term
  //+ MRF.DDt(U)
  + (1.0/porosity)*turbulence->divDevReff(U)
  // Darcy term
  + poreIdx * turbulence->nu() * (1.0/permeability) * U
  // + poreIdx * kinematicViscosity *(1.0/permeability) * U
  // Forchheimer term
  + poreIdx * forchheimerCoeff * mag(U) * U
 ==
    fvOptions(U)
);

UEqn.relax();

fvOptions.constrain(UEqn);

if (piso.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
