import matplotlib.pyplot as plt
import scipy.constants as sc


# CONSTANT
G = sc.G
K = sc.physical_constants['electric constant'][0]


def aceleration(function):
    def wrapper(self, force, time):
        return function(self, (1 / self.mass) * force, time)
    return wrapper


class Vector(object):
    """docstring for Vector"""

    def __init__(self, x1, x2, x3):
        self.x1 = x1
        self.x2 = x2
        self.x3 = x3

    def __str__(self):
        """Para imprimir por pantalla el vector"""
        string = '({:.5f}, {:.5f}, {:.5f})'.format(self.x1, self.x2, self.x3)
        return string

    def __iter__(self):
        return (xi for xi in [self.x1, self.x2, self.x3])

    def __add__(self, vector):
        """suma de vectores, operador +"""
        return Vector(self.x1 + vector.x1, self.x2 + vector.x2,
                      self.x3 + vector.x3)

    def __sub__(self, vector):
        """resta de vectores, operador -"""
        return Vector(self.x1 - vector.x1, self.x2 - vector.x2,
                      self.x3 - vector.x3)

    def __rmul__(self, n):
        """multiplicacion de vector por un escalar"""
        return Vector(n * self.x1, n * self.x2, n * self.x3)

    def __mul__(self, vector):
        """producto cruz, operador *"""
        x1 = self.x2 * vector.x3 - self.x3 * vector.x2
        x2 = self.x1 * vector.x3 - self.x3 * vector.x1
        x3 = self.x1 * vector.x2 - self.x2 * vector.x1
        return Vector(x1, -x2, x3)

    def norm(self):
        """norma de un vector"""
        return (self.x1 ** 2 + self.x2 ** 2 + self.x3 ** 2) ** 0.5

    def direction(self):
        """vector director del vector"""
        return (1 / self.norm()) * self


class Particle(object):
    """docstring for Particle"""

    def __init__(self, mass, charge, position, velocity):
        self.position = position
        self.velocity = velocity
        self.mass = mass
        self.charge = charge

    def __str__(self):
        """Para imprimir por pantalla la particula"""
        string = 'Mass: {:.2f}\n'.format(self.mass)
        string += 'Charge: {:.2f}\n'.format(self.charge)
        string += 'Position: ' + str(self.position) + '\n'
        string += 'Velocity: ' + str(self.velocity) + '\n'

        return string

    def gravitationalForce(self, *particles):
        """Calcula la fuerza gravitacional debida a la interaccion con otras
           particulas"""
        force = Vector(0, 0, 0)

        for particle in particles:
            r = particle.position - self.position
            force += (G * self.mass * particle.mass / r.norm() ** 2) *\
                r.direction()

        return force

    def electricForce(self, *particles):
        """Calcula la fuerza electrica debida a la interaccion con otras
           particulas"""
        force = Vector(0, 0, 0)

        for particle in particles:
            r = self.position - particle.position
            force += (K * self.charge * particle.charge / r.norm() ** 2) *\
                r.direction()

        return force

    def magneticForce(self, *magneticFields):
        """Calcula la fuerza debida a la interaccion con campos magneticos"""
        magneticForce = Vector(0, 0, 0)

        for magneticField in magneticFields:
            magneticForce += self.charge * (self.velocity * magneticField)

        return magneticForce

    @aceleration
    def posEvol(self, aceleration, dt):
        return self.position + dt * \
            self.velocity + (0.5 * dt ** 2) * aceleration

    @aceleration
    def velEvol(self, aceleration, dt):
        return self.velocity + dt * aceleration

    def timeEvol(self, force, dt):
        self.position = self.posEvol(force, dt)
        self.velocity = self.velEvol(force, dt)


def test():
    """programa hecho en clase, con unas pocas modificaciones"""
    particle = Particle(10, 1, Vector(0, 0, 0), Vector(1, 0, 0))

    magneticField = Vector(0, 0, 10)

    x = []
    y = []

    for i in range(100000):
        x.append(particle.position.x1)
        y.append(particle.position.x2)
        force = particle.magneticForce(magneticField)
        particle.timeEvol(force, 0.0001)

    plt.plot(x, y)
    plt.show()


def testParabolic():
    particle = Particle(10, 0, Vector(0, 0, 0), Vector(50, 50, 0))

    i = 0
    x = []
    y = []

    while i < 100000:
        x.append(particle.position.x1)
        y.append(particle.position.x2)

        particle.timeEvol(particle.mass * Vector(0, -9.8, 0), 0.0001)

        i += 1

    plt.plot(x, y)
    plt.show()


def tarea(charge=10, maxIteration=10000, dt=0.01):
    p1 = Particle(10, charge, Vector(0, 0, 0), Vector(0, 0, 0))
    p2 = Particle(10, -charge, Vector(1, 0, 0), Vector(0, 0, 0))

    magneticField = Vector(0, 0, 10)

    x1 = []
    y1 = []
    z1 = []
    x2 = []
    y2 = []
    z2 = []

    for i in range(maxIteration):
        x1.append(p1.position.x1)
        y1.append(p1.position.x2)
        z1.append(p1.position.x3)

        x2.append(p2.position.x1)
        y2.append(p2.position.x2)
        z2.append(p2.position.x3)

        f1 = p1.electricForce(p2) + p1.gravitationalForce(p2) + \
            p1.magneticForce(magneticField)

        f2 = p2.electricForce(p1) + p2.gravitationalForce(p1) + \
            p2.magneticForce(magneticField)

        p1.timeEvol(f1, dt)
        p2.timeEvol(f2, dt)

    plt.plot(x1, y1, '.r', label='Particula 1')
    plt.plot(x2, y2, '.g', label='Particula 2')
    plt.title('Grafico de posicion de las particulas 1 y 2')
    plt.xlabel('Posicion en x')
    plt.ylabel('Posicion en y')
    plt.grid()
    plt.legend(loc=0)
    plt.show()


def main():
    # test()
    # testParabolic()
    # los efectos debido a la gravedad no son tan notables como los electricos
    # por tanto se necesitan muchos mas ciclos para poder apreciarlos
    tarea(maxIteration=10, dt=0.01)


if __name__ == '__main__':
    main()
