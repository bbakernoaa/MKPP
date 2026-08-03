PROGRAM saprc99_diurnal_Main
  USE saprc99_diurnal_Model
  USE saprc99_diurnal_Initialize, ONLY: Initialize
  USE saprc99_diurnal_Integrator, ONLY: INTEGRATE
  USE saprc99_diurnal_Monitor, ONLY: SPC_NAMES

  INTEGER :: i, k
  REAL(kind=dp) :: T, T_END

  INTEGER :: ICNTRL(20)
  REAL(kind=dp) :: RCNTRL(20)
  INTEGER :: ISTATUS(20)
  REAL(kind=dp) :: RSTATUS(20)

  ICNTRL(:) = 0
  RCNTRL(:) = 0.0_dp

  CALL Initialize()

  ! 1440 steps of 60s = 24-hour diurnal cycle (86400 seconds)
  T = TSTART
  DO i = 1, 1440
     T_END = T + 60.0_dp
     CALL INTEGRATE( T, T_END, ICNTRL, RCNTRL, ISTATUS, RSTATUS )
     T = T_END
  END DO

  OPEN(10, FILE="saprc99_fortran_output.csv", STATUS="REPLACE")
  WRITE(10, '(A)') "species_name,concentration"
  DO k = 1, NSPEC
     WRITE(10, '(A,A,ES24.16)') TRIM(SPC_NAMES(k)), ",", C(k)
  END DO
  CLOSE(10)

  WRITE(*,'(A)') "KPP integration complete. Output: saprc99_fortran_output.csv"

END PROGRAM saprc99_diurnal_Main
