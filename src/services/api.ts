import { Book, User, ReadingListItem, FilterOptions } from '@/types/book';

/**
 * API Service - Mock implementation
 * Replace these functions with actual API calls to your C++ backend
 * 
 * Expected C++ Backend Endpoints:
 * - POST /api/auth/login
 * - POST /api/auth/register
 * - GET /api/books
 * - GET /api/books/filter
 * - GET /api/books/:id
 * - GET /api/reading-list/:userId
 * - POST /api/reading-list
 * - DELETE /api/reading-list/:bookId
 */

const API_BASE_URL = 'http://localhost:8080/api';

// Mock data for development (fallback)
const mockBooks: Book[] = [
  {
    id: '1',
    title: 'The Great Gatsby',
    author: 'F. Scott Fitzgerald',
    description: 'A classic American novel set in the Jazz Age that explores themes of wealth, love, and the American Dream.',
    coverImage: 'https://images.unsplash.com/photo-1543002588-bfa74002ed7e?w=400&h=600&fit=crop',
    year: 1925,
    genre: ['Fiction', 'Classic'],
    isbn: '9780743273565',
    rating: 4.5
  },
  {
    id: '2',
    title: '1984',
    author: 'George Orwell',
    description: 'A dystopian social science fiction novel and cautionary tale about the dangers of totalitarianism.',
    coverImage: 'https://images.unsplash.com/photo-1495446815901-a7297e633e8d?w=400&h=600&fit=crop',
    year: 1949,
    genre: ['Fiction', 'Dystopian', 'Science Fiction'],
    isbn: '9780451524935',
    rating: 4.7
  },
  {
    id: '3',
    title: 'To Kill a Mockingbird',
    author: 'Harper Lee',
    description: 'A gripping tale of racial injustice and childhood innocence in the American South.',
    coverImage: 'https://images.unsplash.com/photo-1544947950-fa07a98d237f?w=400&h=600&fit=crop',
    year: 1960,
    genre: ['Fiction', 'Classic'],
    isbn: '9780061120084',
    rating: 4.8
  },
  {
    id: '4',
    title: 'Pride and Prejudice',
    author: 'Jane Austen',
    description: 'A romantic novel that critiques the British landed gentry at the end of the 18th century.',
    coverImage: 'https://cloud.firebrandtech.com/api/v2/image/111/9780785839866/CoverArtHigh/XL',
    year: 1813,
    genre: ['Romance', 'Classic'],
    isbn: '9780141439518',
    rating: 4.6
  },
  {
    id: '5',
    title: 'The Catcher in the Rye',
    author: 'J.D. Salinger',
    description: 'A controversial novel that explores teenage angst and alienation.',
    coverImage: 'https://johnatkinsonbooks.co.uk/wp-content/uploads/2019/07/j-d-salinger-the-catcher-in-the-rye-first-uk-edition-1951.jpg',
    year: 1951,
    genre: ['Fiction', 'Coming-of-age'],
    isbn: '9780316769488',
    rating: 4.0
  }
];

export const authAPI = {
  login: async (email: string, password: string): Promise<User> => {
    try {
      const response = await fetch(`${API_BASE_URL}/auth/login`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password })
      });
      
      if (!response.ok) {
        throw new Error('Login failed');
      }
      
      return await response.json();
    } catch (error) {
      console.error('Login error:', error);
      throw error;
    }
  },

  register: async (email: string, password: string, name: string): Promise<User> => {
    try {
      const response = await fetch(`${API_BASE_URL}/auth/register`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ email, password, name })
      });
      
      if (!response.ok) {
        throw new Error('Registration failed');
      }
      
      return await response.json();
    } catch (error) {
      console.error('Registration error:', error);
      throw error;
    }
  },

  logout: async (): Promise<void> => {
    // Logout is handled client-side
    return Promise.resolve();
  }
};

export const booksAPI = {
  getAll: async (): Promise<Book[]> => {
    try {
      const response = await fetch(`${API_BASE_URL}/books`);
      if (!response.ok) {
        throw new Error('Failed to fetch books');
      }
      return await response.json();
    } catch (error) {
      console.error('Error fetching books:', error);
      return mockBooks; // Fallback to mock data
    }
  },

  filter: async (filters: FilterOptions): Promise<Book[]> => {
    try {
      const params = new URLSearchParams();
      if (filters.author) params.append('author', filters.author);
      if (filters.year) params.append('year', filters.year.toString());
      if (filters.genre) params.append('genre', filters.genre);
      if (filters.prompt) params.append('prompt', filters.prompt);
      
      const response = await fetch(`${API_BASE_URL}/books/filter?${params.toString()}`);
      if (!response.ok) {
        throw new Error('Failed to filter books');
      }
      return await response.json();
    } catch (error) {
      console.error('Error filtering books:', error);
      // Fallback to client-side filtering
      let filtered = [...mockBooks];
      if (filters.author) {
        filtered = filtered.filter(book => 
          book.author.toLowerCase().includes(filters.author!.toLowerCase())
        );
      }
      if (filters.year) {
        filtered = filtered.filter(book => book.year >= filters.year!);
      }
      if (filters.genre) {
        filtered = filtered.filter(book => 
          book.genre.some(g => g.toLowerCase() === filters.genre!.toLowerCase())
        );
      }
      if (filters.prompt) {
        filtered = filtered.filter(book => 
          book.title.toLowerCase().includes(filters.prompt!.toLowerCase()) ||
          book.description.toLowerCase().includes(filters.prompt!.toLowerCase())
        );
      }
      return filtered;
    }
  },

  getById: async (id: string): Promise<Book | null> => {
    try {
      const response = await fetch(`${API_BASE_URL}/books/${id}`);
      if (!response.ok) {
        return null;
      }
      return await response.json();
    } catch (error) {
      console.error('Error fetching book:', error);
      return mockBooks.find(book => book.id === id) || null;
    }
  }
};

export const readingListAPI = {
  get: async (userId: string): Promise<(Book & { status: string })[]> => {
    try {
      const response = await fetch(`${API_BASE_URL}/reading-list/${userId}`);
      if (!response.ok) {
        throw new Error('Failed to fetch reading list');
      }
      return await response.json();
    } catch (error) {
      console.error('Error fetching reading list:', error);
      return [];
    }
  },

  add: async (userId: string, bookId: string, status: string): Promise<void> => {
    try {
      const response = await fetch(`${API_BASE_URL}/reading-list`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ userId, bookId, status })
      });
      if (!response.ok) {
        throw new Error('Failed to add book to reading list');
      }
    } catch (error) {
      console.error('Error adding to reading list:', error);
      throw error;
    }
  },

  remove: async (userId: string, bookId: string): Promise<void> => {
    try {
      const response = await fetch(`${API_BASE_URL}/reading-list/${bookId}?userId=${userId}`, {
        method: 'DELETE'
      });
      if (!response.ok) {
        throw new Error('Failed to remove book from reading list');
      }
    } catch (error) {
      console.error('Error removing from reading list:', error);
      throw error;
    }
  }
};
