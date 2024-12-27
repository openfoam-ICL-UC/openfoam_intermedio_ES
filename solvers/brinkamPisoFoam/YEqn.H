//{
    reaction->correct();
    Qdot = reaction->Qdot();
    volScalarField Yt(0.0*Y[0]);


    forAll(Y, i)
    {
        if (i != inertIndex && composition.active(i))
        {
            volScalarField& Yi = Y[i];            
            // Extract surfaceReactionRate as a scalar fvMatrix
            const fvMatrix<scalar> surfaceReactionRate = reaction->R(Yi);

            fvScalarMatrix YiEqn
            (
                   // Mass acumulation
                   porosity*fvm::ddt(rho_dim*rho, Yi)

                   // Mass diffusion (molecular and turbulent)
                -   rho_dim * fvm::laplacian(Feff*((turbulence->muEff() - turbulence->mu())/Sct + D), Yi)

                   // Convection
                +  rho_dim*rho * icConvection->fvmDiv(phi, Yi)

                ==
                // Convert surface reaction rate to volumetric rate
                // in porous media with cylindrical particles.
                // df.value() is used just for dimensional consistency.
                (4 / df.value()) * (1 - porosity) * surfaceReactionRate

                // Any source term defined in fvOptions, typically 0
                + rho_dim * rho * fvOptions(Yi) 
            );

            // DEBUG PRINTS
            // Info << rho << endl;
            // Info << ((4 / df.value()) * (1 - porosity) * surfaceReactionRate) << endl;
            // Info << surfaceReactionRate << endl;
            // Info << reaction->R(Yi) << endl;
            
            YiEqn.relax();

            fvOptions.constrain(YiEqn);

            YiEqn.solve(mesh.solver("Yi"));

            fvOptions.correct(Yi);

            Yi.clamp_min(0.0);
            Yt += Yi;
        }
    }

    Y[inertIndex] = scalar(1) - Yt;
    Y[inertIndex].clamp_min(0.0);
//}
