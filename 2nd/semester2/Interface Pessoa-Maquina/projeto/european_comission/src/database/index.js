export const API_URL = 'http://localhost:3000';

/**
 * Esta função cria um objeto "db" inteligente.
 * Em vez de ter os dados, ele tem uma função que vai buscar
 * apenas a coleção necessária à API.
 */
export const dbAPI = {
  get: async (endpoint) => {
    try {
      const response = await fetch(`${API_URL}/${endpoint}`);
      if (!response.ok) throw new Error(`Erro ao aceder a ${endpoint}`);
      return await response.json();
    } catch (error) {
      console.error(error);
      return [];
    }
  }
};