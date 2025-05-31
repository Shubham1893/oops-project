In the provided C++ code for the Bank Management System, all four pillars of Object-Oriented Programming (OOP) are utilized. Below is a detailed explanation of each pillar, where it is used in the code, and the rationale for its inclusion.

1. Encapsulation
Definition: Encapsulation is the bundling of data (attributes) and methods (functions) that operate on the data into a single unit or class. It restricts direct access to some of the object's components, which is a means of preventing unintended interference and misuse of the methods and data.

Usage in Code:

Private Members: In the Account class, attributes such as accountNumber, accountHolderName, password, and balance are declared as private. This means they cannot be accessed directly from outside the class.
Public Methods: Public methods like deposit(), withdraw(), checkPassword(), and displayAccountInfo() provide controlled access to the private data. For example, the deposit() method allows users to add money to their account without directly modifying the balance attribute.
Why Encapsulation?: Encapsulation is crucial for maintaining the integrity of the data. By restricting access to the internal state of the object, we can ensure that the data is modified only through well-defined methods, which can include validation and error handling. This helps prevent invalid states and makes the code easier to maintain and debug.

2. Inheritance
Definition: Inheritance is a mechanism where a new class (derived class) can inherit attributes and methods from an existing class (base class). This promotes code reusability and establishes a hierarchical relationship between classes.

Usage in Code:

Base Class: The Account class serves as a base class.
Derived Classes: The CurrentAccount class inherits from the Account class. It can use the methods and attributes of the Account class while also adding its own specific functionality, such as handling overdraft limits.
Why Inheritance?: Inheritance allows for code reuse and the creation of a more organized class structure. By defining common functionality in a base class, derived classes can extend or modify that functionality without duplicating code. This makes the system easier to extend in the future (e.g., adding new account types).

3. Polymorphism
Definition: Polymorphism allows methods to do different things based on the object that it is acting upon, even if they share the same name. This is typically achieved through method overriding and interfaces.

Usage in Code:

Virtual Functions: The withdraw() and displayAccountInfo() methods in the Account class are declared as virtual. This allows derived classes like CurrentAccount to provide their own implementation of these methods.
Dynamic Binding: When a method is called on an object of a derived class through a base class pointer, the derived class's version of the method is executed.
Why Polymorphism?: Polymorphism provides flexibility and the ability to extend the system. It allows the code to be more generic and reusable. For example, if we later add a FixedDepositAccount class, we can implement its own version of withdraw() and displayAccountInfo() without changing the code that uses the Account interface.

4. Abstraction
Definition: Abstraction is the concept of hiding the complex reality while exposing only the necessary parts. It allows focusing on what an object does instead of how it does it.

Usage in Code:

Abstract Class: The Account class is an abstract class because it contains at least one pure virtual function (displayAccountInfo() and withdraw()). This means that it cannot be instantiated directly and must be inherited by other classes.
Interface for Derived Classes: The derived classes (CurrentAccount) must implement the abstract methods, providing specific functionality while hiding the implementation details from the user.
Why Abstraction?: Abstraction simplifies the interaction with complex systems by providing a clear interface. Users of the Account class do not need to understand the underlying implementation details; they only need to know how to interact with the methods provided. This leads to cleaner and more understandable code.

Conclusion
The choice to implement these four pillars in the Bank Management System is driven by the need for a robust, maintainable, and extensible codebase. Each pillar contributes to the overall design and functionality of the system:

Encapsulation protects the integrity of the data.
Inheritance promotes code reuse and a clear class hierarchy.
Polymorphism allows for flexible and dynamic behavior.
Abstraction simplifies the interface and interaction with complex systems.
