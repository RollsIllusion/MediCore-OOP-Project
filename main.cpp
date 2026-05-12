// 
// main
// Entry point for the MediCore Hospital Management System.
//
// Responsibilities:
//   1. Declare all in-memory Storage<T> containers.
//   2. Load all data from .txt files via FileHandler (startup).
//   3. Launch the SFML GUI — the entire program runs from there.
//   4. Return 0 when GUI::run() exits (user closes window).
//
// Rules enforced here:
//   - main() is a sequence of function calls only (per spec).
//   - No global variables (all stores are local to main).
//   - No hardcoded data (everything loaded from .txt files).
// 

#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "FileHandler.h"
#include "FileNotFoundException.h"
#include "gui.h"
#include <iostream>

int main() {
    // 
    // Declare in-memory stores for each entity type.
    // 
    Storage<Patient>      patients;
    Storage<Doctor>       doctors;
    Storage<Appointment>  appointments;
    Storage<Bill>         bills;
    Storage<Prescription> prescriptions;

    // Single admin object loaded directly (only one admin).
    Admin admin;

    // 
    // STARTUP: load all data from .txt files.
    // 
    try {
        FileHandler::loadPatients(patients);
        FileHandler::loadDoctors(doctors);
        FileHandler::loadAdmin(admin);
        FileHandler::loadAppointments(appointments);
        FileHandler::loadPrescriptions(prescriptions);
        FileHandler::loadBills(bills);
    }
    catch (const FileNotFoundException& e) {
        std::cout << "\n[STARTUP ERROR] " << e.what() << "\n";
        std::cout << "Please ensure all required .txt files are present.\n";
        return 1;
    }

    // 
    // Launch the SFML graphical interface.
    // GUI::run() contains the main event loop and returns only
    // when the user closes the window or selects Exit.
    // 
    GUI gui(&patients, &doctors, &appointments, &bills,
        &prescriptions, admin);
    gui.run();

    return 0;
}